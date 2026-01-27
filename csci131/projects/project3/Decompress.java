// Decompress.java
//
// A main function for huffman decompression. This provides the user interface
// and prints results to the screen. It calls Huffman.huffmanDecode() to do all
// the hard work of decompressing/decoding the files.

public class Decompress {

    public static void main(String[] args) {
        System.out.println("Welcome to the Huffman Decompression program.");

        String inputPath, outputPath;
        if (args.length == 2) {
            inputPath = args[0];
            outputPath = args[1];
        } else {
            System.out.print("Input file: ");
            inputPath = StdIn.readLine();
            System.out.print("Output file: ");
            outputPath = StdIn.readLine();
        }

        int[] finalCount = Huffman.huffmanDecode(inputPath, outputPath);         // ##################
        System.out.println("Number of bits read from input file: " + finalCount[0]);
        System.out.println("Number of characters decoded: " + finalCount[1]);

        double average = (finalCount[0] + 0.0) / finalCount[1];
        System.out.printf("Average bits per compressed character: %.3f \n", average);
        System.out.println("Thank you and have a nice day!");
    } // end of main
}
