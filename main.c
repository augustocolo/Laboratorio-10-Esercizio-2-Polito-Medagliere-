#include <stdio.h>
#include <string.h>
#define NUMNATIONS 207

#define true 1
#define false 0

#define firstplace 1
#define secondplace 0.1
#define thirdplace 0.05


int main(int argc, char* argv[]) {
    FILE *fp;
    if ((fp=fopen(argv[1],"r"))==NULL){
        printf("%s file doesn't exist in this directory",argv[1]);
        return 1;
    }

    char import_nation[3 + 1];
    int import_medal;
    char dummy1[5 + 1];
    char dummy2[10 + 1];

    char structure_nation[NUMNATIONS][3 + 1]={"NUL"};
    float structure_summedals[NUMNATIONS]={0};
    int i=0;
    int nation_end;
    //initialize char array structure nation
    for (i=0;i<NUMNATIONS;i++){
        strcpy(structure_nation[i],"NUL");
    }
    //import file
    while (fscanf(fp,"%s %s %s %d\n",dummy1, dummy2, import_nation, &import_medal)!=EOF){
        nation_end=false;
        for (i=0;i<NUMNATIONS && nation_end==false;i++){
            if (strcmp(structure_nation[i],import_nation)==0){
                //somma medaglia
                switch (import_medal){
                    case 1:
                        structure_summedals[i]+=firstplace;
                        break;
                    case 2:
                        structure_summedals[i]+=secondplace;
                        break;
                    case 3:
                        structure_summedals[i]+=thirdplace;
                        break;
                    case 4:
                        break;
                    default:
                        printf("error in database");
                        return 1;
                }
                nation_end=true;
            }else if (strcmp(structure_nation[i], "NUL")==0){
                //end of struct
                //create new nation & somma medaglia
                strcpy(structure_nation[i],import_nation);
                structure_summedals[i]=0;
                switch (import_medal){
                    case 1:
                        structure_summedals[i]+=firstplace;
                        break;
                    case 2:
                        structure_summedals[i]+=secondplace;
                        break;
                    case 3:
                        structure_summedals[i]+=thirdplace;
                        break;
                    case 4:
                        break;
                    default:
                        printf("error in database");
                        return 1;
                }
                nation_end=true;
            }
        }
    }

    //print results
    char podium_names[3][3 + 1];
    float podium_results[3]={0};
    nation_end=false;
    printf("Medaglie d'oro equivalenti: \n");
    for (i=0;i<NUMNATIONS && nation_end==false;i++){
        if (strcmp(structure_nation[i],"NUL")==0){
            nation_end=true;
        } else if (podium_results[0]<structure_summedals[i]){
            podium_results[2]=podium_results[1];
            strcpy(podium_names[2],podium_names[1]);

            podium_results[1]=podium_results[0];
            strcpy(podium_names[1],podium_names[0]);

            podium_results[0]=structure_summedals[i];
            strcpy(podium_names[0],structure_nation[i]);

        } else if (podium_results[1]<structure_summedals[i]){
            podium_results[2]=podium_results[1];
            strcpy(podium_names[2],podium_names[1]);

            podium_results[1]=structure_summedals[i];
            strcpy(podium_names[1],structure_nation[i]);

        } else if (podium_results[2]<structure_summedals[i]){
            podium_results[2]=structure_summedals[i];
            strcpy(podium_names[2],structure_nation[i]);
        }
        if (nation_end==false) {
            printf("%s\t%.2f\n", structure_nation[i], structure_summedals[i]);
        }
    }

    //print podium
    printf("Le prime tre nazioni del medagliere sono:\n");
    for (i=0;i<3;i++){
        printf("%d:\t%s\t%.2f\n",i + 1, podium_names[i],podium_results[i]);
    }

    return 0;
}