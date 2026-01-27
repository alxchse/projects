public class TestLookupCode {
    
    /**
     * A function to test the 'lookupCode' Method. It looks up the given target
     * within the given code file. A message is then printed to indicate whether
     * the answer that was computed matches the desired answer.
     *
     * NOTE: Some characters, like newline ('\n'), carriage return ('\r'), space
     * (' '), and tab ('\t'), can be hard to see in the terminal because they
     * all show up as various kinds of blank space between the quotes. And the
     * special (char)0 character won't show up at all, it will just appear as
     * empty quotes ('').
     */
    public static void test(String codeFileName, String target, char desiredAnswer) {

        char computedAnswer = Huffman.lookupCode(codeFileName, target);
        if (computedAnswer == desiredAnswer)
            System.out.printf("%s was looked up correctly in %s, the return value was '%c' (ascii number %d)\n",
                    target, codeFileName, computedAnswer, (int)computedAnswer);
        else
            System.err.printf("%s was NOT looked up correctly in %s, " +
                    "the return value was '%c' but should have been '%c' (ascii number %d)\n",
                    target, codeFileName, computedAnswer, desiredAnswer, (int)desiredAnswer);

    }

    public static void main(String[] args) {

        test("code-table-small.txt", "Ada",  'L');
        test("code-table-small.txt", "Alan", 'T');
        test("code-table-small.txt", "A", (char)0); // not found

        test("code-table-large.txt", "Fox", ' ');
        test("code-table-large.txt", "Fly", '~');
        test("code-table-large.txt", "Hornet", '\n'); // newline
        test("code-table-large.txt", "Hippopotamus", '\t'); // tab
        test("code-table-large.txt", "Hippo", (char)0); // not found

        // TODO: add a few more tests here
    }

}
