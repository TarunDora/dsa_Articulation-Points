#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define MAX_NAME_LENGTH 50
#define MAX_UNIQUE_NAMES 100

int findIndex(char* arr[], char* target) {
    for (int i = 0; i < MAX_UNIQUE_NAMES; i++) {
        if (!strcmp(arr[i], target)) {
            return i; 
        }
    }
    return -1;
}

int isNameUnique(char *name, char **uniqueNames, int numUniqueNames) {
    for (int i = 0; i < numUniqueNames; i++) {
        if (strcmp(name, uniqueNames[i]) == 0) {
            return 0; 
        }
    }
    return 1; 
}

void dfs(int i, int n, int adj[n][n], int v[n]) {
    v[i] = 1;
    for(int j = 0; j < n; j++)
        if(adj[i][j] == 1)
            if(v[j] == 0) {
                v[j] = 1;
                dfs(j, n, adj, v);
            }
    return;
}

int components(int n, int adj[n][n], int v[n]) {
    for(int i = 0; i < n; i++)
        v[i] = 0;
    int c = 0;
    for(int i = 0; i < n; i++)
        if(v[i] == 0) {
            c++;
            dfs(i, n, adj, v);
        }
    return c;
}

void reachability(int n, int adj[n][n]) {
    int r[n][n];
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            r[i][j] = 0;
    for(int z = 0; z < n; z++) {
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                if(adj[i][j] == 1) {
                    for(int k = 0; k < n; k++) {
                        if(adj[j][k] == 1)
                            r[i][k] = 1;
                    }
                }
            }
        }
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
                adj[i][j] = r[i][j];
    }
}

int main() {
    FILE *file;
    char line[100]; 
    char *token1, *token2; 
    char *uniqueNames[MAX_UNIQUE_NAMES];
    int numUniqueNames = 0;

    file = fopen("a.csv", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    while (fgets(line, sizeof(line), file)) {
        token1 = strtok(line, ",");
        token2 = strtok(NULL, ",");
        
        while (token1 != NULL && token2 != NULL) {
            char *trimmedName1 = strtok(token1, "\r\n");
            char *trimmedName2 = strtok(token2, "\r\n");
            
            if (trimmedName1 != NULL && trimmedName2 != NULL) {
                if (isNameUnique(trimmedName1, uniqueNames, numUniqueNames)) {
                    uniqueNames[numUniqueNames] = malloc(MAX_NAME_LENGTH);
                    strcpy(uniqueNames[numUniqueNames], trimmedName1);
                    numUniqueNames++;
                }

                if (isNameUnique(trimmedName2, uniqueNames, numUniqueNames)) {
                    uniqueNames[numUniqueNames] = malloc(MAX_NAME_LENGTH);
                    strcpy(uniqueNames[numUniqueNames], trimmedName2);
                    numUniqueNames++;
                }
            }

            token1 = strtok(NULL, ",");
            token2 = strtok(NULL, ",");
        }
    }

    fseek(file, 0, SEEK_SET);

    int n = 0;
    while(uniqueNames[n] != NULL) {
        n++;
    }

    int adj[n][n];
    int r[n][n];
    int t[n][n];
    int v[n];

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++)
            adj[i][j] = 0;
    }

    for(int i = 0; i < n; i++)
        v[i] = 0;
while (fgets(line, sizeof(line), file)) {
        token1 = strtok(line, ",");
        token2 = strtok(NULL, ",");
            if (token1 != NULL) {
            token1[strcspn(token1, "\r\n")] = '\0';
        }

        if (token2 != NULL) {
            token2[strcspn(token2, "\r\n")] = '\0';
        }
            int a=findIndex(uniqueNames,token1);
            int b=findIndex(uniqueNames,token2);
            adj[a][b]=1;
            adj[b][a]=1;

        }
    int w, s;

    do {
        printf("enter your choice:\n1. print adjacency matrix\n2. print adjacency list\n3. show the articulation points\n4.resolve articulation points\n");

        scanf("%d", &s);

        switch(s) {
            case 1: {
                printf("  ");
                for(int i = 0; i < n; i++)
                    printf("%d", i);
                printf("\n");

                for(int i = 0; i < n; i++) {
                    printf("%d", i);
                    printf(" ");
                    for(int j = 0; j < n; j++)
                        printf("%d", adj[i][j]);
                    printf("\n");
                }
                printf("\n");
                break;
            }
            case 2: {
                for(int i = 0; i < n; i++) {
                    printf("%s->", uniqueNames[i]);
                    for(int j = 0; j < n; j++) {
                        if(adj[i][j] == 1) {
                            printf("%s->", uniqueNames[j]);
                        }
                    }
                    printf("\n");
                }
                break;
            }
            case 3: {
                int e=0;
                for(int x = 0; x < n; x++) {
                    for(int i = 0; i < n; i++) {
                        for(int j = 0; j < n; j++)
                            t[i][j] = adj[i][j];
                    }
                    for(int y = 0; y < n; y++) {
                        t[x][y] = 0;
                        t[y][x] = 0;
                    }

                    for(int i = 0; i < n; i++) {
                        for(int j = 0; j < n; j++)
                            r[i][j] = t[i][j];
                    }

                    reachability(n, r);

                    if(components(n, t, v) > 3) {
                       printf("%s is an articulation point\n", uniqueNames[x]);}}
                       break;}
            case 4: {
                int e=0;
                for(int x = 0; x < n; x++) {
                    for(int i = 0; i < n; i++) {
                        for(int j = 0; j < n; j++)
                            t[i][j] = adj[i][j];
                    }
                    for(int y = 0; y < n; y++) {
                        t[x][y] = 0;
                        t[y][x] = 0;
                    }

                    for(int i = 0; i < n; i++) {
                        for(int j = 0; j < n; j++)
                            r[i][j] = t[i][j];
                    }

                    reachability(n, r);

                    if(components(n, t, v) > 3) {
                       //printf("%s is an articulation point\n", uniqueNames[x]);
                       e=e+1;
                        int flag = 0;

                        for(int i = 0; i < n; i++) {
                            for(int j = 0; j < n; j++) {
                                if(adj[x][i] == 1 && adj[x][j] == 1 && i != j && r[i][j] == 0) {
                                    printf("Connect %s and %s to bypass articulation point at %s\n", uniqueNames[i], uniqueNames[j], uniqueNames[x]);
                                    adj[i][j] = 1;
                                    adj[j][i] = 1;
                                    flag = 1;
                                    break;
                                }
                            }
                            if(flag)
                                break;
                        }
                    }
                }
                break;
            }
        }
        printf("do you want to continue (1/0):");
        scanf("%d", &w);
    } while(w);
    
    fclose(file);
    return 0;
}