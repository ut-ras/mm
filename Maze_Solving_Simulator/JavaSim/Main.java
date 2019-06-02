public class Main {
    static int[][] map = new int[16][16];
    static int[] top = {14,13,12,11,10,9,8,7,7,8,9,10,11,12,13,14};

    public static void main(String[] args) {
        Mouse utmm = new Mouse();
        populateMap(map,top);
        if(utmm.opennorth()){
            utmm.move(1);
        }
        else{
            utmm.move(0);
        }
        while(map[utmm.getx()][utmm.gety()]!=0){
            movtoJunc(utmm);
            chooseDir(utmm);
            dEnd(utmm);
        }
        revChooseDir(utmm);
        while(utmm.getx()!=0 && utmm.gety()!=0){
            movtoJunc(utmm);
            revChooseDir(utmm);
            dEnd(utmm);
        }
    }

    public static void populateMap(int map[][], int top[]){
        for(int i = 0; i < 16; i++){
            map[0][i] = top[i];
        }
        for(int i = 1; i < 8; i++){
            for(int j = 0; j < 16; j++){
                map[i][j] = map[i-1][j] - 1;
            }
        }
        for(int i = 0; i < 16; i++){
            map[8][i] = map[7][i];
        }
        for(int i = 9; i < 16; i++){
            for(int j = 0; j < 16; j++){
                map[i][j] = map[i-1][j] + 1;
            }
        }
    }

    public static void printMap(int map[][], Mouse m){
        for(int i = 15; i > -1; i--){
            for(int j = 0; j < 16; j++){
                if(m.getx()==j && m.gety()==i){
                    System.out.printf("**|");
                }
                else{
                    System.out.printf("%02d|", map[j][i]);
                }
            }
            System.out.println();
            for(int j = 0; j < 16; j++){
                System.out.printf("---");
            }
            System.out.println();
        }
        System.out.println();
        System.out.println();
    }

    public static void movtoJunc(Mouse m){
        while(m.pathnum() == 2){
            if(m.openeast() && m.getBackdir() != 0){
                m.move(0);
            }
            else if(m.opennorth() && m.getBackdir() != 1){
                m.move(1);
            }
            else if(m.openwest() && m.getBackdir() != 2){
                m.move(2);
            }
            else{
                m.move(3);
            }
        }
    }

    public static void chooseDir(Mouse m){
        if(m.pathnum() > 2){
            int lowestval = 99;
            int godir = 0;
            if(m.openeast() && lowestval > map[m.getx()+1][m.gety()] && map[m.getx()+1][m.gety()] != -1){
                lowestval = map[m.getx()+1][m.gety()];
                godir = 0;
            }
            if(m.opennorth() && lowestval > map[m.getx()][m.gety()+1] && map[m.getx()][m.gety()+1] != -1){
                lowestval = map[m.getx()][m.gety()+1];
                godir = 1;
            }
            if(m.openwest() && lowestval > map[m.getx()-1][m.gety()] && map[m.getx()-1][m.gety()] != -1){
                lowestval = map[m.getx()-1][m.gety()];
                godir = 2;
            }
            if(m.opensouth() && lowestval > map[m.getx()][m.gety()-1] && map[m.getx()][m.gety()-1] != -1){
//                lowestval = map[m.getx()][m.gety()-1];
                godir = 3;
            }
            m.move(godir);
        }
    }

    public static void revChooseDir(Mouse m){
        if(m.pathnum() > 2){
            int highestVal = -1;
            int godir = 0;
            if(m.opensouth() && highestVal < map[m.getx()][m.gety()-1] && map[m.getx()][m.gety()-1] != -1){
                highestVal = map[m.getx()][m.gety()-1];
                godir = 3;
            }
            if(m.openwest() && highestVal < map[m.getx()-1][m.gety()] && map[m.getx()-1][m.gety()] != -1){
                highestVal = map[m.getx()-1][m.gety()];
                godir = 2;
            }
            if(m.opennorth() && highestVal < map[m.getx()][m.gety()+1] && map[m.getx()][m.gety()+1] != -1){
                highestVal = map[m.getx()][m.gety()+1];
                godir = 1;
            }
            if(m.openeast() && highestVal < map[m.getx()+1][m.gety()] && map[m.getx()+1][m.gety()] != -1){
//                highestVal = map[m.getx()+1][m.gety()];
                godir = 0;
            }
            m.move(godir);
        }
    }

    public static void dEnd(Mouse m){
        if(m.pathnum()<2){
            m.setdir(m.getBackdir());
            movtoJunc(m);
            map[m.getprex()][m.getprey()] = -1;
        }
    }

    /*public static void movtoJunc(Mouse m){
            if(m.openeast() && m.getdir() != 2){
                m.move(0);
            }
            else if(m.opennorth() && m.getdir() != 3){
                m.move(1);
            }
            else if(m.openwest() && m.getdir() != 0){
                m.move(2);
            }
            else{
                m.move(3);
            }
            if(m.pathnum()<2){
                m.setdir((m.getdir()+2)%4);
                System.out.println(m.getx() + " " + m.gety());
                while(m.pathnum() < 3){
                    if(m.openeast() && m.getdir() != 2){
                        m.move(0);
                    }
                    else if(m.opennorth() && m.getdir() != 3){
                        m.move(1);
                    }
                    else if(m.openwest() && m.getdir() != 0){
                        m.move(2);
                        System.out.println("pre " + m.getprex() + " " + m.getprey());
                    }
                    else{
                        m.move(3);
                    }
                }
                System.out.println("curr " + m.getx() + " " + m.gety());
                System.out.println("pre " + m.getprex() + " " + m.getprey());
                map[m.getprex()][m.getprey()] = -1;
            }
    }*/

    /*public static void chooseDir(Mouse m){
            int lowestval = 99;
            int godir = 0;
            if(m.openeast() && lowestval > map[m.getx()+1][m.gety()] && map[m.getx()+1][m.gety()] != -1){
                lowestval = map[m.getx()+1][m.gety()];
                godir = 0;
            }
            if(m.opennorth() && lowestval > map[m.getx()][m.gety()+1] && map[m.getx()][m.gety()+1] != -1){
                lowestval = map[m.getx()][m.gety()+1];
                godir = 1;
            }
            if(m.openwest() && lowestval > map[m.getx()-1][m.gety()] && map[m.getx()-1][m.gety()] != -1){
                lowestval = map[m.getx()-1][m.gety()];
                godir = 2;
            }
            if(m.opensouth() && lowestval > map[m.getx()][m.gety()-1] && map[m.getx()][m.gety()-1] != -1){
                lowestval = map[m.getx()][m.gety()-1];
                godir = 3;
            }
            m.move(godir);
            if(m.pathnum()<2){
                m.setdir((m.getdir()+2)%4);
                while(m.pathnum() < 3){
                    if(m.openeast() && m.getdir() != 2){
                        m.move(0);
                    }
                    else if(m.opennorth() && m.getdir() != 3){
                        m.move(1);
                    }
                    else if(m.openwest() && m.getdir() != 0){
                        m.move(2);
                        System.out.println("pre " + m.getprex() + " " + m.getprey());
                    }
                    else{
                        m.move(3);
                    }
                }
                map[m.getprex()][m.getprey()] = -1;
            }
    }*/
}
