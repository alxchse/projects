// Alexandra Chase
// September 21 2022
// This system lists all the numbers less than 100 that are divisible by 3,
// 5, and both 3 & 5. 


public class Divisible {
    public static void main(String[] args) {

int num;

StdOut.print("Divisible by 3: ");
for (num = 1; num < 100; num++)
    {
    if (num%3 == 0)
    StdOut.print(num + ", ");
    }
StdOut.println();

StdOut.print("Divisible by 5: ");
for (num = 1; num < 100; num++)
    {
    if (num%5 == 0)
    StdOut.print(num + ", ");
    }
StdOut.println();

StdOut.print("Divisible by both 3 and 5: ");
for (num = 1; num < 100; num++)
    {
    if (num%3 == 0 && num%5 == 0)
    StdOut.print(num + ", ");
    }
StdOut.println();
    }
}