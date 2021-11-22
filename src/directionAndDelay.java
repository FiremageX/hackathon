import java.io.*;
import java.util.*;
import java.util.concurrent.TimeUnit;
public class directionAndDelay {
    public static void main(String[] args) throws IOException, InterruptedException{
        Scanner in = new Scanner(new File("path.out"));
        //PrintWriter out = new PrintWriter(new File("directions.out"));
        int length = in.nextInt() + 1;
        int speed = in.nextInt();
        int x[] = new int[length];
        int y[] = new int[length];
        int dirIndex[] = new int[length - 1];
        boolean lastWentForward = true;
        for(int i = 0; i<length; i++) {
            x[i] = in.nextInt();
            y[i] = in.nextInt();
        }   
        System.out.println("Start going forward");
        for (int i = 1; i < x.length; i++){
            
            if(x[i] == x[i-1] + 1) {
                //right = 1
                dirIndex[i-1] = 1;
            }
            else if (x[i] == x[i-1] - 1) {
                //left = 3
                dirIndex[i-1] = 3;
            }
            else if (y[i] == y[i-1] + 1) {
                //up = 0
                dirIndex[i-1] = 0;
            }
            else if (y[i] == y[i-1] - 1) {
                //down = 2
                dirIndex[i-1] = 2;
            }

            //determine when the user has to turn
            if(i >=2) {
            	if(i == x.length - 1) {
                    System.out.println("You have reached your destination");
            	}
            	else if(!lastWentForward && dirIndex[i-1] == dirIndex[i-2]){
                    lastWentForward = true;
                    	System.out.println("Continue Forward");
                }
                else if(dirIndex[i-1] == (dirIndex[i-2]+1)%4) {
                	System.out.println("Turn right");
                    lastWentForward = false;
                }
                else if (dirIndex[i-1] == (dirIndex[i-2]+3)%4) {
                	System.out.println("Turn left");
                    lastWentForward = false;
                }
            }
            TimeUnit.MILLISECONDS.sleep(1000/speed);
        }
        //out.close();
        in.close();
    }
}