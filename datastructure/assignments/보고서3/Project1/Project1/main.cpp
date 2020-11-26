#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <time.h>
int tmeal[33];
int ameal[33] = { 48, 72, 86, 51, 80, 79, 38, 73, 82, 42, 65, 82, 52, 76, 86, 43, 68, 86, 41, 70, 91, 44, 73, 84, 41, 81, 93, 41, 78, 81, 35, 67, 89 };
int tbolus[33];
double abolus[33];
int tmealPM[33] = { 75, 111, 70, 119, 100, 91, 111, 95, 77, 91, 6, 119, 5, 5, 69, 96, 59, 82, 65, 54, 34, 60, 80, 25, 100, 77, 45, 47, 10, 105, 4, 106, 72 };
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
void initValue(FILE* fs) {

    int i, j = -1440;

    fprintf(fs, "tmeal: ");// j(하루 1440분)+[6시 12시 19시] + tmealPM 
    for (i = 0; i < 11; i++) {
        j += 1440;
        tmeal[i * 3] = 360 + j + tmealPM[i * 3];
        tmeal[i * 3 + 1] = 720 + j + tmealPM[i * 3 + 1];
        tmeal[i * 3 + 2] = 1140 + j + tmealPM[i * 3 + 2];

        fprintf(fs, "%d %d %d ", tmeal[i * 3], tmeal[i * 3 + 1], tmeal[i * 3 + 2]);
    }
    srand(time);
    fprintf(fs, "\nAmeal: ");
    for (i = 0; i < 11; i++) {      //랜덤값을 초기에 받고 변수로 저장해서 사용중 새로 받으려면 밑에 3줄 주석 해제 
    //   ameal[i*3]=45+rand()%20-10; 
    //   ameal[i*3+1]=75+rand()%20-10;
    //   ameal[i*3+2]=85+rand()%20-10;      
        fprintf(fs, "%d %d %d ", ameal[i * 3], ameal[i * 3 + 1], ameal[i * 3 + 2]);
    }

    fprintf(fs, "\ntbolus: ");//식사시간 - 45분 
    for (i = 0; i < 11; i++) {
        tbolus[i * 3] = tmeal[i * 3] - 45;
        tbolus[i * 3 + 1] = tmeal[i * 3 + 1] - 45;
        tbolus[i * 3 + 2] = tmeal[i * 3 + 2] - 45;
        fprintf(fs, "%d %d %d ", tbolus[i * 3], tbolus[i * 3 + 1], tbolus[i * 3 + 2]);
    }

    fprintf(fs, "\nabolus: ");//식사량/15 한 값  
    for (i = 0; i < 11; i++) {
        abolus[i * 3] = (double)ameal[i * 3] / 15;
        abolus[i * 3 + 1] = (double)ameal[i * 3 + 1] / 15;
        abolus[i * 3 + 2] = (double)ameal[i * 3 + 2] / 15;
        fprintf(fs, "%.2lf %.2lf %.2lf ", abolus[i * 3], abolus[i * 3 + 1], abolus[i * 3 + 2]);
    }
}
void creatScript(FILE* fs) {
    int i;
    fprintf(fs, "simulation info\n\n%%Tsimul=11\n%%QTsimul=day\n%%simToD=0\n\nclosed loop info\n\n%%Tclosed=264\n%%%QTclosed=hour\n%%Treg=15840\n\n");
    fprintf(fs, "Open loop info\n\n%%Qbasal=quest\n\n");

    fprintf(fs, "meals info\n\n");
    fprintf(fs, "%%Tmeal=[");
    for (i = 0; i < 33; i++) {
        fprintf(fs, "%d ", tmeal[i]);
    }fprintf(fs, "]\n");

    fprintf(fs, "%%Ameals=[");
    for (i = 0; i < 33; i++) {
        fprintf(fs, "%d ", ameal[i]);
    }fprintf(fs, "]\n%%Dmeals=[15]\n%%Qmeals=total\n");

    fprintf(fs, "\nbolus info\n%%Tbolus=[");
    for (i = 0; i < 33; i++) {
        fprintf(fs, "%d ", tbolus[i]);
    }fprintf(fs, "]\n%%QTbolus=min\n");

    fprintf(fs, "%%Abolus=[");
    for (i = 0; i < 33; i++) {
        fprintf(fs, "%.2lf ", abolus[i]);
    }fprintf(fs, "]\n");

}
int main(int argc, char* argv[]) {
    FILE* iV, * sC;
    iV = fopen("scriptValue.txt", "w"); initValue(iV);//  sC=fopen("script.txt","w");creatScript(sC);fclose(iV);
    sC = fopen("script.txt", "w"); creatScript(sC); fclose(sC);

    return 0;
}