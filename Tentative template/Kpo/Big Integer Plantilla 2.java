import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.math.BigInteger;


public class Main {

    public static void main(String[] args) throws IOException {
    	//lee un nuevo input
        InputStreamReader isr = new InputStreamReader(System.in);
        BufferedReader br = new BufferedReader(isr);
        StringBuffer sb = new StringBuffer("");
        int cases=Integer.parseInt(br.readLine());
            for(int i=0;i<cases;i++) {
               String[] str=br.readLine().split(" ");
               str[0]=reverse(str[0]);
               str[1]=reverse(str[1]);
               BigInteger x,y;
               x=new BigInteger(str[0]);
               y=new BigInteger(str[1]);
               String temp=reverse(x.add(y)+"");
               x=new BigInteger(temp);
               sb.append(x).append("\n");
            }
            System.out.print(sb);
    }
    
    static String reverse(String h){
        StringBuilder sb=new StringBuilder(h);
        return sb.reverse().toString();
    }
}