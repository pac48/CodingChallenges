package problems;

import java.util.Arrays;
import utilities.*;

public class MagicIndex extends MyCode {
    private Integer[] A;

    @Override
    public void run() {
        Common.print("A: ");
        Common.printArray(A);
        Common.print("sorted A: ");
        Arrays.sort(A);
        Common.printArray(A);
        Common.print("The magic index is: ");
        Common.println(findIndex());
        Common.print("The magic index faster is: ");
        Common.print(findIndexFaster());
    }

    public MagicIndex(){
        A = new Integer[]{12,5,2,2,9,1};
    }

    private int findIndexFaster(){
        return recurse(A, 0,A.length-1);
    }
    private int recurse(Integer[] a, int start, int end){
        if (end < start){
            return -1;
        }
        int mid = (start+end)/2;
        if (a[mid] == mid){
            return a[mid];
        } else if(a[mid] > mid){
            return recurse(a,start,mid-1);
        } else {
            return recurse(a,mid+1,end);
        }
    }
    private int findIndex(){
        for (int i =0;i<A.length;i++){
            if (A[i]==i){
                return A[i];
            }
        }
        return -1;
    }
}
