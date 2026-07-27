# Elios Hoxholli and Alexandra Chase
# amchas26@g.holycross, ehoxho27@g.holycross.edu
# classifier.py
# Decision Tree Classifier — CSCI 347 Project 3

import csv
import math
import sys
from scipy.stats import chi2

# SECTION 1: DATA LOADING
# Read the attributes file and CSV datasets into Python data structures.

def load_attributes(filepath):
    # Reads the attributes file and returns a dict mapping
    # attribute name -> list of possible values.
    # e.g. {"response": ["republican","democrat"], "crime": ["y","n","?"], ...}

    attributes = {}
    with open(filepath, newline='') as f:
        reader = csv.reader(f, quotechar='|')
        for row in reader:
            clean = [item.strip() for item in row]
            attributes[clean[0]] = clean[1:]
    return attributes

def load_data(filepath):
    # Reads a CSV dataset and returns:
    #   - header: list of column names  e.g. ["response", "crime", ...]
    #   - data:   list of rows          e.g. [["democrat","y","n",...], ...]
    # The header row is separated from the data rows.

    rows = []
    with open(filepath, newline='') as f:
        reader = csv.reader(f, quotechar='|')
        for row in reader:
            rows.append([item.strip() for item in row])
    header = rows[0]
    data   = rows[1:]
    return header, data

# SECTION 2: ENTROPY AND INFORMATION GAIN
# Core math functions used by the tree builder.

def calculate_entropy(target_values):
    # Calculates the entropy of a list of target classifications.
    total_instances = len(target_values)
    
    # If the list is empty, there is zero entropy
    if total_instances == 0:
        return 0.0

    # 1. Count the occurrences of each class (democrat vs. republican)
    class_counts = {}
    for value in target_values:
        if value in class_counts:
            class_counts[value] += 1
        else:
            class_counts[value] = 1

    # 2. Calculate the entropy using the formula
    entropy = 0.0
    for count in class_counts.values():
        probability = count / total_instances
        
        # We multiply the probability by the log2 of the probability, 
        # and subtract it from our running total
        entropy -= probability * math.log2(probability)
    return entropy

def calculate_information_gain(data, attribute_index, target_index):
    # Calculates the information gain of splitting the data using a specific attribute.

    # 1. Calculate the base entropy of the target first
    target_values = [row[target_index] for row in data]
    base_entropy = calculate_entropy(target_values)
    total_rows = len(data)
    
    # 2. Find all the unique labels for the attribute we are evaluating (e.g., 'y', 'n', '?')
    attribute_values = [row[attribute_index] for row in data]
    unique_labels = set(attribute_values)
    
    # 3. Calculate the Remainder (expected number of bits per example over all branches)
    remainder = 0.0
    for label in unique_labels:
        # Filter the target values for ONLY the rows where this attribute equals the label
        subset_targets = [row[target_index] for row in data if row[attribute_index] == label]
        # Calculate the proportion of rows this label takes up
        proportion = len(subset_targets) / total_rows
        # Multiply proportion by the entropy of this subset and add to the remainder
        remainder += proportion * calculate_entropy(subset_targets)
        
    # 4. Information Gain = Base Entropy - Remainder
    information_gain = base_entropy - remainder
    return information_gain

# SECTION 3: TREE BUILDING
# recursively constructs the decision tree from training data.
# a node in the decision tree is just a Python dictionary
# there are two kinds:
#
# A DECISION node has the following features:
#   type: decision
#   attribute: physician-fee-freeze       the attribute being tested
#   attribute_index: 4                    its column index in the data
#   branches: {                           one entry per possible value
#       y: <another node>
#       n: <another node>
#       ?: <another node>
#
# A LEAF node looks like this:
#   type: leaf
#   value: republican                     the predicted class

def majority_class(data, target_index):
    # used when we need to make a decision but can't split further or there's no matching vals for an attribute
    # in case of a tie, pythons max() picks
    
    # count how many times each class appears
    # return the class with the highest count
    class_counts = {}                                    
    for row in data:
        label = row[target_index]
        if label in class_counts:
            class_counts[label] += 1
        else:
            class_counts[label] = 1
    return max(class_counts, key=class_counts.get)      


def build_tree(data, attributes, header, target_index):
    # recursively builds a decision tree using the algorithm we learned in class.
    # takes:
        # data          : list of rows without header
        # attributes    : dict mapping attribute name to list of possible values
                        # BUT only includes attributes NOT yet used as split points.
        # header        : the full header row
                        # we need it to look up column indices by name.
        # target_index  : the column index of the target class label (always 0 for "response")
    # returns:
        # a decision node dict or a leaf node dict

    # get indices for all the target classes within data
    target_values = [row[target_index] for row in data]

    # BASE CASE 1: all examples have the same class label
    # if every row in our data is "democrat"
    # there is nothing left to split so return a leaf with that class
    if len(set(target_values)) == 1:
        return {"type": "leaf", "value": target_values[0]}

    # BASE CASE 2: no attributes left to split data further
    # weve used up every attribute but the data is still mixed...
    # the best we can do is return a leaf with the majority class
    if len(attributes) == 0:
        return {"type": "leaf", "value": majority_class(data, target_index)}

    # BASE CASE 3: no data in the level
    # this shouldn't happen at the top, but can happen in
    # recursive calls if a branch has no matching rows
    # return a leaf with the majority class of whatever data we have
    if len(data) == 0:
        return {"type": "leaf", "value": majority_class(data, target_index)}

    # RECURSIVE CASE: pick the best attribute to split on.
    best_attribute = None      # to hold the winning attribute name
    best_gain = -1             # hold the winning gain value

    # loop through every attribute that hasn't been used yet
    # find which column this attribute lives in using the header row
    # call calculate IG we'd get by using this attribute
    # if this attribute is better than everything else, remember it
    for attr_name in attributes:
        attr_index = header.index(attr_name)
        gain = calculate_information_gain(data, attr_index, target_index)         
        if gain > best_gain:                                                      
            best_attribute = attr_name
            best_gain = gain

    # get the column index of the winning attribute
    best_attr_index = header.index(best_attribute)

    # build a node to test the best attribute
    node = {
        "type": "decision",
        "attribute": best_attribute,
        "attribute_index": best_attr_index,
        "branches": {} # we'll fill this set in below
    }

    # remove best_attribute from the available attributes for child nodes now that shes been used
    # we make a NEW dict without best_attribute,
    # so the og attributes dict is not modified, which is important for other branches
    remaining_attributes = {
        name: values
        for name, values in attributes.items()
        if name != best_attribute
    }
    
    # build one branch for each possible value of best_attribute
    # for example, most possible values are [y, n, ?] so we build 3 branches
    # loop through every possible value this attribute can take
    for value in attributes[best_attribute]:

        # filter the data to use only the rows where the attribute equals value
        # like if value is y, keep just he rows where column best_attr_index is y 
        subset = [row for row in data if row[best_attr_index] == value]

        # if no rows matched this value, we can't recurse...
        # so instead, create a leaf using the majority class of the CURRENT PARENT'S data
        if len(subset) == 0:
            node["branches"][value] = {
                "type": "leaf",
                "value": majority_class(data, target_index)
            }

        else:
            # recursively build a subtree using only the matching rows
            # and the remaining unused attributes.
            node["branches"][value] = build_tree(
                subset,               # only rows that match this branch
                remaining_attributes, # attributes not yet used
                header,               # full header (never changes)
                target_index          # target column (never changes)
            )
    return node

    # loop through every possible value this attribute can take
    for value in attributes[best_attribute]:
        # filter the data to only the rows where this attribute equals value
        # like if value is "y", keep only rows where column best_attr_index is "y"
        subset = [row for row in data if row[best_attr_index] == value]

        # if no rows matched this value, we can't recurse 
        # so instead, create a leaf using the majority class of the CURRENT parents data
        if len(subset) == 0:
            node["branches"][value] = {
                "type": "leaf",
                "value": majority_class(data, target_index)
            }

        else:
            # recursively build a subtree using only the matching rows
            # and the remaining (unused) attributes
            node["branches"][value] = build_tree(
                subset,               # only rows that match this branch
                remaining_attributes, # attributes not yet used
                header,               # full header (never changes)
                target_index          # target column (never changes)
            )
    return node

# SECTION 4: CHI-SQUARED PRUNING
# After the tree is built, prune branches that aren't statistically significant.

def chi_squared_test(data, attribute_index, target_index, classes):
    # Performs a chi-squared test on a proposed split.
    # Returns the p-value. If p-value > significance level, the split is not
    # meaningful and the node should be pruned back to a leaf.

    # The chi-squared statistic measures whether the distribution of classes
    # in each branch differs from what you'd expect by random chance.

    # Get all unique values for this attribute in the data
    attribute_values = set(row[attribute_index] for row in data)
    total = len(data)

    # Count how many of each class exist overall (needed for expected counts)
    class_totals = {c: sum(1 for row in data if row[target_index] == c) for c in classes}
    chi_stat = 0.0

    for value in attribute_values:
        # Rows in this branch
        branch = [row for row in data if row[attribute_index] == value]
        branch_size = len(branch)
        if branch_size == 0:
            continue

        for cls in classes:
            # Observed: how many of this class actually appear in this branch
            observed = sum(1 for row in branch if row[target_index] == cls)
            # Expected: how many we'd expect if the split were random
            expected = branch_size * (class_totals[cls] / total)
            
            # Avoid division by zero
            if expected > 0:
                chi_stat += (observed - expected) ** 2 / expected

    # degrees of freedom = (num_values - 1) * (num_classes - 1)
    df = (len(attribute_values) - 1) * (len(classes) - 1)
    if df <= 0:
        return 1.0  # No meaningful split possible, treat as not significant

    # scipy gives us P(chi^2 <= chi_stat), so we subtract from 1 to get the p-value
    p_value = 1 - chi2.cdf(chi_stat, df)
    return p_value

def prune_tree(node, data, header, target_index, classes, significance):
    # Recursively prunes the tree using chi-squared testing.
    # If a decision node's split is not statistically significant
    # (p-value > significance), replace it with a leaf (majority class).
    # This is called AFTER build_tree — you build first, then prune.

    # Leaves cannot be pruned further
    if node["type"] == "leaf":
        return node

    attr_index = node["attribute_index"]

    # Recursively prune all child branches first (bottom-up pruning)
    for value, child in node["branches"].items():
        subset = [row for row in data if row[attr_index] == value]
        node["branches"][value] = prune_tree(
            child, subset, header, target_index, classes, significance
        )

    # Now test whether THIS node's split is worth keeping
    p_value = chi_squared_test(data, attr_index, target_index, classes)

    # If the split is not significant, replace this whole node with a leaf
    if p_value > significance:
        return {"type": "leaf", "value": majority_class(data, target_index)}
    return node

# SECTION 5: CLASSIFICATION
# Use the finished tree to classify new examples.

def classify(tree, row, header):
    # Walks one row down the tree and returns the predicted class label.
    # Follows the branches based on the row's attribute values until
    # it reaches a leaf, then returns the leaf's value.
    # Base case: we've reached a leaf
    if tree["type"] == "leaf":
        return tree["value"]

    # Find which value this row has for the attribute being tested
    attr_index = tree["attribute_index"]
    row_value  = row[attr_index]

    # Follow the matching branch (if the value isn't in the tree,
    # fall back to the first branch — handles unseen values gracefully)
    if row_value in tree["branches"]:
        return classify(tree["branches"][row_value], row, header)
    else:
        # Unseen value: pick any branch (majority would be ideal but this is rare)
        fallback = next(iter(tree["branches"].values()))
        return classify(fallback, row, header)

# SECTION 6: EVALUATION
# Compute recognition rate and confusion matrix.

def evaluate(tree, data, header, classes, target_index):
    # Classifies every row in data and returns:
      # - recognition_rate: float, percentage of correct predictions
      # - confusion_matrix: dict of dicts, confusion_matrix[predicted][actual] = count
    # Initialize an empty confusion matrix
    # Rows = predicted class, Columns = actual class
    confusion_matrix = {pred: {actual: 0 for actual in classes} for pred in classes}
    correct = 0
    
    for row in data:
        actual = row[target_index]  # use the passed-in index of intended class
        predicted = classify(tree, row, header)

        if predicted == actual:
            correct += 1

        # Guard against predicted values not in our known classes
        if predicted in confusion_matrix and actual in confusion_matrix[predicted]:
            confusion_matrix[predicted][actual] += 1

    recognition_rate = (correct / len(data)) * 100
    return recognition_rate, confusion_matrix

def print_evaluation(recognition_rate, confusion_matrix, classes, dataset_name):
    # Prints the recognition rate and confusion matrix for one dataset.
    print(f"\n-- {dataset_name} Results --")
    print(f"Recognition Rate: {recognition_rate:.2f}%")

    # Print confusion matrix header
    print("\nConfusion Matrix (rows=predicted, cols=actual):")
    col_width = 15
    print(" " * col_width + "".join(c.ljust(col_width) for c in classes))

    for pred in classes:
        row_str = pred.ljust(col_width)
        row_str += "".join(str(confusion_matrix[pred][actual]).ljust(col_width) for actual in classes)
        print(row_str)

# SECTION 7: TREE PRINTING AND STATISTICS
# Print the tree with indentation and compute depth stats.

def print_tree(node, attributes_dict, indent=0):
    # Recursively prints the tree with indentation showing depth.
    # Matches the required output format from the instructions.

    prefix = "    " * indent  # 4 spaces per level of depth

    if node["type"] == "leaf":
        print(f"{prefix}Leaf with value: {node['value']}")
        return

    print(f"{prefix}Testing {node['attribute']}")
    for value, child in node["branches"].items():
        print(f"{prefix}    Branch {value}")
        print_tree(child, attributes_dict, indent + 1)


def get_depths(node, current_depth=0):
    # Returns a list of depths of all leaf nodes.
    # Used to compute max, min, and average depth.

    if node["type"] == "leaf":
        return [current_depth]

    depths = []
    for child in node["branches"].values():
        depths.extend(get_depths(child, current_depth + 1))
    return depths


def count_nodes(node):
    # Returns (total_nodes, decision_nodes) counts for the whole tree.

    if node["type"] == "leaf":
        return 1, 0  # 1 total node, 0 decision nodes

    total    = 1  # count this decision node itself
    decision = 1

    for child in node["branches"].values():
        child_total, child_decision = count_nodes(child)
        total    += child_total
        decision += child_decision

    return total, decision


def print_tree_stats(tree):
    # Prints the node counts and depth statistics for the tree.

    total_nodes, decision_nodes = count_nodes(tree)
    depths = get_depths(tree)

    print(f"\n-- Decision Tree Summary --")
    print(f"Total Nodes: {total_nodes}")
    print(f"Decision Nodes: {decision_nodes}")
    print(f"Maximum Depth: {max(depths)}")
    print(f"Minimum Depth: {min(depths)}")
    print(f"Average Depth of Root-to-Leaf: {sum(depths) / len(depths):.3f}")

# SECTION 8: MAIN
# Ties everything together. Reads arguments, loads data, builds tree,
# optionally prunes, evaluates, and prints all required output.

def main():
    # read arguments
    # expected: python3 classifier.py <attributes file> <train set> <test set> <significance for pruning>
    if len(sys.argv) < 4:
        print("Usage: python3 classifier.py <attributes> <training-set> <testing-set> [significance]")
        sys.exit(1)

    attributes_file = sys.argv[1]
    train_file = sys.argv[2]
    test_file = sys.argv[3]

    # significance is optional, if not given, no pruning is applied
    significance = float(sys.argv[4]) if len(sys.argv) == 5 else None

    # load data
    attributes_dict = load_attributes(attributes_file)
    header, train_data = load_data(train_file)
    _, test_data  = load_data(test_file)

    target_name = list(attributes_dict.keys())[0]   # first value = target attribute in nodes
    target_index = header.index(target_name)
    classes = attributes_dict[target_name]

    # build the three
    # all attributes except the target class ("response") are available to split on
    training_attributes = {
        name: values
        for name, values in attributes_dict.items()
        if name != "response"
    }

    tree = build_tree(train_data, training_attributes, header, target_index)

    # prune tree if necesseary
    if significance is not None:
        tree = prune_tree(tree, train_data, header, target_index, classes, significance)

    # print the decision tree
    print("\n-- Printing Decision Tree --")
    print_tree(tree, attributes_dict)
    print_tree_stats(tree)
    
    # evaluate training set
    train_rate, train_matrix = evaluate(tree, train_data, header, classes, target_index)
    print_evaluation(train_rate, train_matrix, classes, "Training Set")

    # evaluate test set
    test_rate,  test_matrix  = evaluate(tree, test_data,  header, classes, target_index)
    print_evaluation(test_rate, test_matrix, classes, "Test Set")

if __name__ == "__main__":
    main()
