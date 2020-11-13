package problems;

import utilities.Common;
import utilities.MyCode;
import java.util.HashMap;

public class TripleStep extends MyCode {
    private HashMap<Integer,Integer> memo;
    private int numberStairs;
    @Override
    public void run() {
        Common.print("The number of combinations is: ");
        Common.print(findNumber());
    }

    public TripleStep(int num){
        memo = new HashMap<>();
        numberStairs = num;
    }
    private int findNumber(){
        int numberStairs = 5;
        return recurse(numberStairs);
    }
    private int recurse( int n){
        if (n<0){
            return 0;
        } else if (n==0){
            return 1;
        } else {
            int r1;
            int r2;
            int r3;
            if (memo.get(n-1)==null)
                r1 = recurse(n-1);
            else{
                r1 =  memo.get(n-1);
                memo.put(n-1,r1);}
            if (memo.get(n-2)==null){
                r2 = recurse(n-2);
                memo.put(n-2,r2); }
            else
                r2 =  memo.get(n-2);
            if (memo.get(n-3)==null){
                r3 = recurse(n-3);
                memo.put(n-3,r3);}
            else
                r3 =  memo.get(n-3);
            return r1+r2+r3;
        }
    }

}
