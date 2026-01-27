// Alexandra Chase
// 30 October 2022
// CSCI 131
// project 3 
// I am using this as a placeholder for the second part of my project until I finish debugging
// the first part, LookupCode

    public static int [] huffmanDecode(String inputFileEncoded, String outputFileDecoded) {

        In inFile = new In();
        Out outFile = new Out();
        String target2 = "";
        char character = inFile.readChar();


    public static void main(String[] args, int[] Counters) {

        String entry1 = args[0];
        String entry2 = args[1];
        int bits = Counters[0];
        int decoded = Counters[1];
        double average = ((double)bits/(double)decoded);

        huffmanDecode(entry1, entry2);

        StdOut.println("Welcome to the Huffman Decompression program.");
        StdOut.println("Input file: " + entry1);
        StdOut.println("Output file: " + entry2);
        StdOut.println("Number of bits read from input file: " + bits);
        StdOut.println("Number of characters decoded: " + decoded);
        StdOut.println("Average number of bits per compressed character: " + average);
        StdOut.println("Thank you and have a nice day!");


    }                                                   // end of main