package utilities;

import sun.util.locale.provider.FallbackLocaleProviderAdapter;

import java.util.ArrayList;

public class Common {

    static public void printArray(Object[] A){
        for (int i =0;i<A.length;i++){
            System.out.print(A[i]);
            System.out.print(" ");
        }
        System.out.println("");
    }
    static public void printArray(int[] A){
        for (int i =0;i<A.length;i++){
            System.out.print(A[i]);
            System.out.print(" ");
        }
        System.out.println("");
    }
    static public void print(Object s){
        System.out.print(s);
    }
    static public void println(Object s){
        System.out.println(s);
    }
    static public boolean arrayEqual(ArrayList<Integer> s1, ArrayList<Integer> s2){
        return s1.equals(s2);
        //if (s2.size()!=s1.size())
        //  return false;
        //for (int i=0;i<s1.size();i++) {
        // if (!s1.get(i).equals(s2.get(i)))
        //s1.equals(s2);
        //return false;
        //}
    }
}
