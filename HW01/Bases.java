/**
 * CS 2110 Fall 2021 HW1 Part 2 - Coding with bases
 *
 * @author Lucas Luwa
 *
 *         Global rules for this file: - You may not use more than 2
 *         conditionals per method. Conditionals are if-statements, if-else
 *         statements, or ternary expressions. The else block associated with an
 *         if-statement does not count toward this sum. - You may not use more
 *         than 2 looping constructs per method. Looping constructs include for
 *         loops, while loops and do-while loops. - You may not use nested
 *         loops. - You may not declare any file-level variables. - You may not
 *         use switch statements. - You may not use the unsigned right shift
 *         operator (>>>) - You may not write any helper methods, or call any
 *         method from this or another file to implement any method. Recursive
 *         solutions are not permitted. - The only Java API methods you are
 *         allowed to invoke are: String.length() String.charAt() - You may not
 *         invoke the above methods from string literals. Example:
 *         "12345".length() - When concatenating numbers with Strings, you may
 *         only do so if the number is a single digit.
 *
 *         Method-specific rules for this file: - You may not use
 *         multiplication, division or modulus in any method, EXCEPT
 *         decimalStringToInt (where you may use multiplication only) - You may
 *         declare exactly one String variable each in intToHexString and and
 *         binaryStringToOctalString.
 */
public class Bases {
    /**
     * Convert a string containing ASCII characters (in binary) to an int.
     *
     * You do not need to handle negative numbers. The Strings we will pass in will
     * be valid binary numbers, and able to fit in a 32-bit signed integer.
     *
     * Example: binaryStringToInt("111"); // => 7
     */
    public static int binaryStringToInt(String binary) {
        int counter = 0;
        int length = binary.length();
        for (int i = 0; i < length; i++) {
            // System.out.println(binary.charAt(i));
            if (binary.charAt(length - i - 1) == '1') {
                counter += 1 << i;
                // System.out.println("Counter" + counter);
            }
        }
        return counter;
    }

    /**
     * Convert a string containing ASCII characters (in decimal) to an int.
     *
     * You do not need to handle negative numbers. The Strings we will pass in will
     * be valid decimal numbers, and able to fit in a 32-bit signed integer.
     *
     * Example: decimalStringToInt("46"); // => 46
     *
     * You may use multiplication in this method.
     */
    public static int decimalStringToInt(String decimal) {
        int counter = 0;
        int starter = 1;
        int length = decimal.length();
        for (int i = 0; i < length; i++) {
            int num = decimal.charAt(length - 1 - i) - 48;
            counter += starter * num;
            starter *= 10;
        }
        return counter;
    }

    /**
     * Convert a string containing ASCII characters (in octal) to an int.
     *
     * You do not need to handle negative numbers. The Strings we will pass in will
     * be valid octal numbers, and able to fit in a 32-bit signed integer.
     *
     * Example: octalStringToInt("27"); // => 23
     */
    public static int octalStringToInt(String octal) {
        int counter = 0;
        int length = octal.length();
        int indexer = 0;
        for (int i = 0; i < length; i++) {
            int front = octal.charAt(length - i - 1) - 48;
            counter += front << indexer;
            indexer += 3;
            // System.out.println("front: "+ front);
            // System.out.println(counter);
            // System.out.println(indexer);
        }
        // System.out.println("breaker");
        return counter;
    }

    /**
     * Convert a int into a String containing ASCII characters (in hex).
     *
     * You do not need to handle negative numbers. The String returned should
     * contain the minimum number of characters necessary to represent the number
     * that was passed in.
     *
     * Example: intToHexString(166); // => "A6"
     *
     * You may declare one String variable in this method.
     */
    public static String intToHexString(int hex) {
        String holder = "";
        int indexer = 0;
        int current = 0;
        while (hex>0 | indexer != 0 | hex==0 & holder == ""){
                current += (hex & 1) << indexer;

            hex = hex>>1;
            indexer++;
            if(indexer == 4 & current>9){
                //System.out.println(current);
                holder = (char)('A'+current-10)+holder;
                //System.out.println(holder);
                indexer = 0;
                current = 0;
            }
            else if(indexer == 4 & current<10){
                holder = current + holder;
                indexer = 0;
                current = 0;
            }
        }
        return holder;
    }

    /**
     * Convert a String containing ASCII characters representing a number in binary
     * into a String containing ASCII characters that represent that same value in
     * octal.
     *
     * The output string should only contain numbers. You do not need to handle
     * negative numbers. The length of all the binary strings passed in will be of
     * size 24. The octal string returned should contain 8 characters.
     *
     * Example: binaryStringToOctalString("000001101010000111100100"); // =>
     * "01520744"
     *
     * You may declare one String variable in this method.
     */
    public static String binaryStringToOctalString(String binary) {
        int binaryNum = 0;
        int counter = 0;
        int indexer = 0;
        String holder = "";
        for (int i = 0; i < binary.length(); i++) {
            // if (binary.charAt(binary.length()-1-i) == '1') {
            //     binaryNum += 1;
            //     //System.out.println("1st"+ binaryNum);
            // }
            // if (binary.charAt(binary.length()-2-i) == '1') {
            //     binaryNum += 1 << 1;
            //     //System.out.println("2nd"+ binaryNum);
            // }
            // if (binary.charAt(binary.length()-3-i) == '1') {
            //     binaryNum += 1 << 2;
            //     //System.out.println("3rd"+ binaryNum);
            // }
            // holder = binaryNum + holder;
            // binaryNum = 0;
            if (binary.charAt(binary.length()-1-i) == '1'){
                binaryNum+= 1<<indexer;
            } 
            indexer++;
            counter++;
            if(counter==3){
                counter = 0;
                indexer = 0;
                holder = binaryNum + holder;
                binaryNum =0;
            }
        }
        //System.out.println(Integer.toBinaryString(binaryNum));
        return "" +holder;
    }
}
