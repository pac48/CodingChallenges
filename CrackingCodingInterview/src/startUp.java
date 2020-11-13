import problems.*;
import utilities.Problem;

public class startUp {

    public static void main(String[] args) {
        new Problem("Find magic a number in array.", new MagicIndex());
        new Problem("How many ways can a child walk up stairs (5) with 1, 2, or 3 steps.", new TripleStep(5));
        new Problem("Return all subsets of a set.", new PowerSet());
        new Problem("Make change for $1 with 1, 5, 10, and 25 cents.", new MakeChange(100));
    }

}
