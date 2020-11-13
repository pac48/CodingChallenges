package utilities;

public class Problem  {

    public Problem(String prompt, MyCode code){
        Common.println("");
        Common.println(prompt);
        printHR();
        code.run();
        end();
    }

    private void end(){
        Common.println("");
        printHR();
    }

    private void printHR(){
        Common.println("____________________________________");
    }

}
