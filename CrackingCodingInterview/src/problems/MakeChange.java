package problems;

import utilities.Common;
import utilities.MyCode;

import java.lang.reflect.Array;
import java.util.HashMap;


public class MakeChange extends MyCode {
    private final HashMap<Integer,Integer> memo;
    private final HashMap<Coin,Integer> memo2;
    private final HashMap<Coin,Integer> combinations;
    private final int total;
    @Override
    public void run() {
        Common.print("The number of combinations is: ");
        Common.println(findNumber());
        Common.println("The options are: ");
        findNumber2();
        Common.print("with a total of: ");
        Common.print(combinations.keySet().size());

    }
    public class Coin{
        Integer [] values;
      public Coin(Integer [] val){
          values = getCoinCopy(val);
      }
        @Override
        public boolean equals(Object obj){
          Coin coin2 = (Coin) obj;
          for (int i =0;i<4;i++){
              if (coin2.values[i] != values[i])
                      return false;
          }
          return true;
      }
        @Override
        public int hashCode()
        {
            return getSum(this.values);
        }
    }

    public MakeChange(int num){
        memo = new HashMap<>();
        memo2 = new HashMap<>();
        combinations = new HashMap<>();
        total = num;
    }
    private int findNumber(){
        return recurse(total);
    }
    private void findNumber2(){
        Coin coins = new Coin(new Integer[]{0,0,0,0});
        recurse2(coins);
    }
    private Integer getSum(Integer[] coins){
        int sum = 0;
        int [] value={1,5,10,25};
        for(int i =0;i<4;i++){
            sum+=coins[i]*value[i];
        }
        return sum;
    }

    private int recurse( int n) {
        if (n < 0) {
            return 0;
        } else if (n == 0) {
            return 1;
        } else {
            int r1;
            int r2;
            int r3;
            int r4;
            if (memo.get(n - 1) == null) {
                r1 = recurse(n - 1);
                memo.put(n - 1, r1);
            } else
                r1 = memo.get(n - 1);

            if (memo.get(n - 5) == null) {
                r2 = recurse(n - 5);
                memo.put(n - 5, r2);
            } else
                r2 = memo.get(n - 5);

            if (memo.get(n - 10) == null) {
                r3 = recurse(n - 10);
                memo.put(n - 10, r3);
            } else
                r3 = memo.get(n - 10);

            if (memo.get(n - 25) == null) {
                r4 = recurse(n - 25);
                memo.put(n - 25, r4);
            } else
                r4 = memo.get(n - 25);

            return r1 + r2 + r3 + r4;
        }
    }
        private Integer[] getCoinCopy(Integer[] coins){
            Integer [] coinsCopy = new Integer[]{0,0,0,0};
            for (int i =0;i<4;i++){
                coinsCopy[i] = coins[i];
            }
            return coinsCopy;
        }
        private void recurse2( Coin coins){
            if (memo2.get(coins)!=null)
                return;
            if (total - getSum(coins.values) < 0){
            } else if (total - getSum(coins.values)==0){
                if (combinations.get(coins)==null) {
                    Common.printArray(coins.values);
                    combinations.put(coins, 1);
                }
            } else {
                Coin coins1 = new Coin(getCoinCopy(coins.values));
                coins1.values[0]++;
                Coin coins2 = new Coin(getCoinCopy(coins.values));
                coins2.values[1]++;
                Coin coins3 = new Coin(getCoinCopy(coins.values));
                coins3.values[2]++;
                Coin coins4 = new Coin(getCoinCopy(coins.values));
                coins4.values[3]++;
                recurse2(coins1);
                memo2.put(coins1,1);
                recurse2(coins2);
                memo2.put(coins2,1);
                recurse2(coins3);
                memo2.put(coins3,1);
                recurse2(coins4);
                memo2.put(coins4,1);
            }
    }

}
