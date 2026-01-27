// Alexandra Chase
// CSCI 131
// 30 October 2022
// Project 3: Huffman Project

public class Huffman{

    public static char lookupCode(String codeFileName, String target){

        In inFile = new In(codeFileName);                               // opens existing file to be read
        String name;                                                    // person name from file
        int i;                                                          // integer corresponding with name
        String c;                                                       // comment corresponding with name
        char ch = (char)0;                                              // integer i converted to ASCII character

        while (!inFile.isEmpty()) {                                     // stops when empty
            name = inFile.readString();                                 // read name 
            i = inFile.readInt();                                       // read integer
            c = inFile.readLine();                                      // read comment
                if (name.equalsIgnoreCase(target)) {                    // if string name equals target name
                    ch = (char)i;                                       // convert int i to ASCII
                    break;                                              // break the loop
                }
                else {
                    ch = (char)0;                                       // in case name doesnt match list
                }   
        }
        return ch;                                                      // returns character
    }                                                                   // end of lookupCode

    public static int[] huffmanDecode(String inputFile, String outputFile) {

        In inFile = new In(inputFile);                                  // open input file
        Out outFile = new Out(outputFile);                              // open output file
        String target2 = "";                                            // new empty target string
        int bits = 0;                                                   // number of bits in file
        int decoded = 0;                                                // number of decoded chars in file
        char value;                                                     // code to be matched

        while (!inFile.isEmpty()) {                                     // while file isnt empty
            char character = inFile.readChar();                         // read next character in file
                if ((character == '0') || (character == '1')) {         // if character is a 0 or 1
                    target2 = target2 + character;                      // change target to include that last char
                    bits++;                                             // add to the number of bits
                    value = lookupCode("code-table.txt", target2);      // look up values in file 
                        if (value != (char)0) {                         // if value has corresponding char
                            outFile.print(value);                       // print value in decompressed file
                            target2 = "";                               // revert string to empty
                            decoded++;                                  // add to number of decompressed chars
                        }
                }
        }
        inFile.close();                                                 // close input file
        outFile.close();                                                // close output file



        int[] Counters = new int[2];                                    // new array to keep track of counters
            Counters[0] = bits;                                         // total number of bits
            Counters[1] = decoded;                                      // total number of decoded chars

        if (!target2.equals(""))                                        // error checking
            StdOut.println("Input file contained invalid data.");

        return Counters;                                                // return array
    }                                                                   // end of huffmanDecode
    
}                                                                       // end of class

