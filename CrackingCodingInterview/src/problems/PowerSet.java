package problems;

import utilities.Common;
import utilities.MyCode;
import java.util.ArrayList;
import java.util.Collections;

// page 348
public class PowerSet extends MyCode {
    private final ArrayList<Integer> set;

    @Override
    public void run() {
        Common.print("The set is: ");
        Collections.sort(set);
        Common.println(set);
        Common.print("The subsets are: ");
        ArrayList< ArrayList<Integer> > subsets = getSubsets();
        for (ArrayList<Integer> subset : subsets) {
            Common.println(subset);
        }
    }

    public PowerSet(){
        set = new ArrayList<>();
        for (int i =0;i<5;i++){
            set.add(i);
        }
    }


    private boolean find(ArrayList< ArrayList<Integer> > subsets, ArrayList<Integer> s){
        for (ArrayList<Integer> subset : subsets) {
            if (Common.arrayEqual(s,subset))
                return true;
        }
        return false;
    }

    private ArrayList< ArrayList<Integer> >  getSubsets(){
        ArrayList< ArrayList<Integer> > subsets = new ArrayList<>();
        subsets.add(new ArrayList<Integer>()); // need to include empty
        recurse(set,subsets);
        return subsets;
    }

    private void recurse( ArrayList<Integer> s, ArrayList< ArrayList<Integer> > subsets){
        for (int i=0;i<s.size();i++){
            ArrayList<Integer> subset = new ArrayList<>();
            for (int j=0;j<s.size();j++) {
                if (j!=i)
                    subset.add(s.get(j));
            }
            if (!find(subsets,subset))
                subsets.add(subset);
            recurse(subset,subsets);
        }
    }

}
