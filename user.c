#include "graph.h"

    //truth table of gates
    int and[3][3]={{0,0,0,},{0,1,2},{0,2,2}};
    int or[3][3]={{0,1,2},{1,1,1},{2,1,2}};
    int xor[3][3]={{0,1,2},{1,0,2},{2,2,2}};
    int not[3]={1,0,2};
    int from[3]={0,1,2};

    int ReadVec(FILE *fvec,PATTERN *vector){
        int i,j,a;
        char line[Mpi+2];
        printf("hello readvec");
        j=0;
        while(!feof(fvec)){
            fgets(line, Mpi+1, fvec);
            for(i=0;i<strlen(line);i++){
                a=strlen(line);
                if( line[i]=='0')           vector[j].vector[i]=0;
                else if(line[i]=='1')       vector[j].vector[i]=1;
                else if(line[i]=='x'||'X')  vector[j].vector[i]=2;
            }
            j++;
        }
        return j;
        /*for(i=0; i<j;i++){
            printf("%s",vector[i].vector);
        }
            printf("\n");
        */
    }
    void LogicSimulation(NODE *graph, PATTERN *pattern, int Total, int Max, FILE *result){
        LIST *temp;
        int i,j,count;
        int x=0,y=0;
        //printf("Hello???????");
        for(j=0;j<Total;j++){
            //printf("Hello World");
            count=0;
            for(i=1;i<=Max;i++){
                if(graph[i].Type==INPT){
                        graph[i].Cval=pattern[j].vector[count];
                        printf("%d",graph[i].Cval);
                        count++;
                }
                else{
                    if(graph[i].Type==FROM){
                        temp=graph[i].Fin;
                        x=graph[temp->id].Cval;
                        while(temp!=NULL){
                            if(temp->next!=NULL){
                                y=graph[temp->next->id].Cval;
                                graph[i].Cval=from[x];
                                temp=temp->next;
                            }
                        }
                    }
                    else if(graph[i].Type==AND){
                        temp=graph[i].Fin;
                        x=graph[temp->id].Cval;
                        while(temp!=NULL){
                            if(temp->next!=NULL){
                                y=graph[temp->next->id].Cval;
                                graph[i].Cval=and[x][y];
                                temp=temp->next;
                            }
                        }
                    }
                    else if(graph[i].Type==OR){
                        temp=graph[i].Fin;
                        x=graph[temp->id].Cval;
                        while(temp!=NULL){
                            if(temp->next!=NULL){
                                y=graph[temp->next->id].Cval;
                                graph[i].Cval=or[x][y];
                                temp=temp->next;
                            }
                        }
                    }
                    else if (graph[i].Type==NOT){
                        temp=graph[i].Fin;
                        x=graph[temp->id].Cval;
                        while(temp!=NULL){
                            graph[i].Cval=not[x];
                        }
                    }
                    else if (graph[i].Type==NAND){
                        int a=0;
                        temp=graph[i].Fin;
                        x=graph[temp->id].Cval;
                        while(temp!=NULL){
                            if(temp->next!=NULL){
                                y=graph[temp->next->id].Cval;
                                a=and[x][y];
                                graph[i].Cval=not[a];
                                temp=temp->next;
                            }
                        }
                    }
                    else if (graph[i].Type==NOR){
                        int a=0;
                        temp=graph[i].Fin;
                        x=graph[temp->id].Cval;
                        while(temp!=NULL){
                            if(temp->next!=NULL){
                                y=graph[temp->next->id].Cval;
                                a=or[x][y];
                                graph[i].Cval=not[a];
                                temp=temp->next;
                            }
                        }
                    }
                    else if (graph[i].Type==XOR){
                        temp=graph[i].Fin;
                        x=graph[temp->id].Cval;
                        while(temp!=NULL){
                            if(temp->next!=NULL){
                                y=graph[temp->next->id].Cval;
                                graph[i].Cval=xor[x][y];
                                temp=temp->next;
                            }
                        }
                    }
                    else if (graph[i].Type==XNOR){
                        int a=0;
                        temp=graph[i].Fin;
                        x=graph[temp->id].Cval;
                        while(temp!=NULL){
                            if(temp->next!=NULL){
                                y=graph[temp->next->id].Cval;
                                a=xor[x][y];
                                graph[i].Cval=not[a];
                                temp=temp->next;
                            }
                        }
                    }
                }
                if(graph[i].Po == 1){
                    printf("%d\n",graph[i].Cval);				
                    putc('0'+ graph[i].Cval, result);
                }
            }
            
        }   
    }