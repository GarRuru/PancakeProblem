import java.util.Scanner;
import java.lang.Math;

public class Pancake
{
    private int totalPancakes;
    private int state[];
    

    public Pancake(int totalPancakes)
    {
        this.totalPancakes = totalPancakes;
        state = new int[this.totalPancakes];
    }

    public void printCake()
    {
        int count = 0;
        System.out.print("[");
        for(i : state)
        {
            System.out.printf("%d",i);
            if(i)
        }
    }

    public void Read()
    {
        Scanner ss = new Scanner();
        for(int i=0;i<totalPancakes;i++)
        {
            ss.nextInt(state[i]);
        }
    }

    public boolean isGoal()
    {
        for(i=0;i<totalPancakes-1;i++)
        {
            if(state[i] > state[i+1])
                return false;
        }
        return true;
    }

    public int gapNumber()
    {
        int gap = 0;
        for(int i=0;i<totalPancake-1;i++)
        {
            if(abs(state[i]-state[i+1])!=1)
                gap++;
        }
        return gap;
    }

    public void makeSuccessor()
    {
        Scanner ss = new Scanner();
        int currentG;
        int lastAction;
        ss.nextInt(currentG);
        ss.nextInt(lastAction);
        for(int i=2;i<totalPancakes;i++)
        {
            if(i == lastAction)
                continue;
            else
            {
                int 
                for(int j=0;j<i;j++)
                {

                }
            }
        }
    }

    public static void main(String argv[])
    {
        Scanner input = new Scanner();
        int ncases,cake;
        input.nextInt(ncases);
        while(ncases--)
        {
            input.nextInt(cake);
            Pancake pcake = new Pancake(cake);
            pcake.Read();
            if(pcake.isGoal())
                System.out.println("YES");
            else System.out.println("NO");

            System.out.println(pcake.gapNumber());
        }
    }
}