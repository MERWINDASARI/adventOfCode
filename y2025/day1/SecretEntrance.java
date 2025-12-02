package y2025.day1;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class SecretEntrance {
    public static void main(String[] args) {
        Scanner sc = null;
        try {
            sc = new Scanner(new File("y2025/day1/input1.txt"));
        } catch (FileNotFoundException e) {
            System.out.println("File Not Found: "+e.getMessage());
            System.exit(1);
        }
        int pos=50;
        int prePos=50;
        int offset=0;
        int res=0;
        boolean isPartOne=false;
        while(sc.hasNextLine()){
            String line = sc.nextLine();
            offset=Integer.parseInt(line.substring(1));
            if(!isPartOne) {
                res+=(offset/100);
                offset=offset%100;
            }
            if(line.charAt(0)=='L') offset=-offset;
            pos+=offset;
            if(isPartOne){
                if(pos<0) pos+=100;
                pos=pos%100;
                if(pos==0) res++;
            }else{
                if(pos<=0){
                    if(prePos!=0) res++;
                    pos+=100;
                }
                else if(pos>99) res++;
                pos=pos%100;
                prePos=pos;
            }
            //System.out.println("At "+pos+" "+res);
        }

        System.out.println("Final Result: "+res);
        
    }
}
