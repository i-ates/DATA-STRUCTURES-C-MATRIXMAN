#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

struct file {
    char *name;
    int **array;
    int row;
    int column;
};

void veczeros(struct file *filearray, int *file_count, char *name, int length, FILE *pFile) {
    int i;
    bool check=false;
    for(i=0;i<*file_count;i++){
        if(!strcmp(filearray[i].name,name)){
            check=true;
            break;
        }
    }
    if(check==false){
        filearray[*file_count].array = (int **) malloc(length * sizeof(int *));
        filearray[*file_count].name = (char *) malloc(strlen(name) * sizeof(char)+1);
        strcpy(filearray[*file_count].name, name);
        filearray[*file_count].column = 1;
        filearray[*file_count].row = length;
        for (i = 0; i < length; i++) {
            filearray[*file_count].array[i] = 0;

        }
        fprintf(pFile, "created vector %s %d\n", name, length);
        for (i = 0; i < length; i++) {
            fprintf(pFile, "%d ", filearray[*file_count].array[i]);
        }
        fprintf(pFile, "\n");

        *file_count = *file_count + 1;

    }else{
        fprintf(pFile,"error\n");
    }


}

void matzeros(struct file *filearray, int *file_count, char *name, int column, int row, FILE *pFile) {
    int i;
    int j;

    bool check=false;
    for(i=0;i<*file_count;i++){
        if(!strcmp(filearray[i].name,name)){
            check=true;
            break;
        }
    }
    if(check==false){
        filearray[*file_count].array = (int **) malloc(column * sizeof(int *));
        for (i = 0; i < column; i++) {
            filearray[*file_count].array[i] = (int *) malloc(row * sizeof(int));
        }
        filearray[*file_count].name = (char *) malloc(strlen(name) * sizeof(char)+1);

        strcpy(filearray[*file_count].name, name);
        filearray[*file_count].row = row;
        filearray[*file_count].column = column;
        for (i = 0; i < column; i++) {
            for (j = 0; j < row; j++) {
                filearray[*file_count].array[i][j] = 0;
            }
        }
        fprintf(pFile, "created matrix %s %d %d\n", name, column, row);
        for (i = 0; i < column; i++) {
            for (j = 0; j < row; j++) {
                fprintf(pFile,"%d ", filearray[*file_count].array[i][j]);
            }
            fprintf(pFile,"\n");
        }
        *file_count = *file_count + 1;
    }else{
        fprintf(pFile,"error\n");
    }



}

void vecread(struct file *filearray, char *v[], int *file_count, char *name,FILE *pFile) {
    FILE *fPtr2;
    int i;
    int j;
    int c;
    char ch;
    int count_row = 0;
    int count_column = 1;
    //choose matrix and vector file
    char *temp = (char *) malloc((strlen(name) ) * sizeof(char)+1);
    strcpy(temp, name);
    //foldername+filename
    char *location = (char *) malloc((strlen(v[0]) + strlen(name) ) * sizeof(char)+1);
    strcpy(location, v[0]);
    strcat(location, name);
    //opening matrix and vector files
    fPtr2 = fopen(location, "r");
    do {
        ch = getc(fPtr2);
        if (ch == '\n') {
            ch = getc(fPtr2);
            if (ch != EOF) {
                count_column++;
            }
        }
        if (ch == ' ') {
            count_row++;
        }

    } while (ch != EOF);
    name = strtok(name, ".");
    count_row = (count_row / count_column) + 1;
    filearray[*file_count].row = count_row;
    filearray[*file_count].column = count_column;
    filearray[*file_count].name = (char *) malloc(strlen(temp) * sizeof(char)+1);
    strcpy(filearray[*file_count].name, name);
    if (filearray[*file_count].column == 1) {
        filearray[*file_count].array = (int **) malloc(filearray[*file_count].row * sizeof(int *));


    } else {
        filearray[*file_count].array = (int **) malloc(filearray[*file_count].column * sizeof(int *));
        for (i = 0; i < filearray[*file_count].column; i++) {
            filearray[*file_count].array[i] = (int *) malloc(filearray[*file_count].row * sizeof(int));
        }
    }
    fclose(fPtr2);
    fPtr2 = fopen(location, "r");
    if (filearray[*file_count].column != 1) {
        for (i = 0; i < filearray[*file_count].column; i++) {
            for (j = 0; j < filearray[*file_count].row; j++) {
                fscanf(fPtr2, "%d", &filearray[*file_count].array[i][j]);

            }
        }

    } else {
        for (i = 0; i < filearray[*file_count].row; i++) {
            fscanf(fPtr2, "%d", &filearray[*file_count].array[i]);
        }
    }


    *file_count = *file_count + 1;
    fclose(fPtr2);
    free(location);


    int index;
    for (i = 0; i < *file_count; i++) {
        if (!strcmp(filearray[i].name, name)) {
            index = i;
            break;
        }

    }
    fprintf(pFile, "read vector %s %d\n", temp, filearray[index].row);
    for (i = 0; i < filearray[index].row; i++) {

        fprintf(pFile, "%d ", filearray[index].array[i]);
    }
    fprintf(pFile, "\n");
    free(temp);

}

void matread(struct file *filearray, char *v[], int *file_count, char *name, FILE *pFile) {
    FILE *fPtr2;
    int i;
    int j;
    int c;
    char ch;
    int count_row = 0;
    int count_column = 1;
    //choose matrix and vector file
    char *temp = (char *) malloc((strlen(name) ) * sizeof(char)+1);
    strcpy(temp, name);
    //foldername+filename
    char *location = (char *) malloc((strlen(v[0]) + strlen(name)) * sizeof(char)+1);
    strcpy(location, v[0]);
    strcat(location, name);
    //opening matrix and vector files

    fPtr2 = fopen(location, "r");
    do {
        ch = getc(fPtr2);
        if (ch == '\n') {
            ch = getc(fPtr2);
            if (ch != EOF) {
                count_column++;
            }
        }
        if (ch == ' ') {
            count_row++;
        }

    } while (ch != EOF);
    name = strtok(name, ".");

    count_row = (count_row / count_column) + 1;
    filearray[*file_count].row = count_row;
    filearray[*file_count].column = count_column;
    filearray[*file_count].name = (char *) malloc(strlen(temp) * sizeof(char)+1);
    strcpy(filearray[*file_count].name, name);
    if (filearray[*file_count].column == 1) {
        filearray[*file_count].array = (int **) malloc(filearray[*file_count].row * sizeof(int *));


    } else {
        filearray[*file_count].array = (int **) malloc(filearray[*file_count].column * sizeof(int *)+2);
        for (i = 0; i < filearray[*file_count].column; i++) {
            filearray[*file_count].array[i] = (int *) malloc(filearray[*file_count].row * sizeof(int));
        }
    }
    fclose(fPtr2);
    fPtr2 = fopen(location, "r");
    if (filearray[*file_count].column != 1) {
        //fprintf(pFile, "***row %d column %d\n",filearray[fileIndex].row,filearray[fileIndex].column);
        for (i = 0; i < filearray[*file_count].column; i++) {
            for (j = 0; j < filearray[*file_count].row; j++) {
                fscanf(fPtr2, "%d", &filearray[*file_count].array[i][j]);

            }
        }

    } else {
        for (i = 0; i < filearray[*file_count].row; i++) {
            fscanf(fPtr2, "%d", &filearray[*file_count].array[i]);
        }
    }


    *file_count = *file_count + 1;
    fclose(fPtr2);
    free(location);


    int index;

    for (i = 0; i < *file_count; i++) {
        if (!strcmp(filearray[i].name, name)) {
            index = i;
            break;
        }
    }
    fprintf(pFile, "read matrix %s %d %d\n", temp, filearray[index].column, filearray[index].row);
    for (i = 0; i < filearray[index].column; i++) {
        for (j = 0; j < filearray[index].row; j++) {
            fprintf(pFile, "%d ", filearray[index].array[i][j]);
        }
        fprintf(pFile, "\n");
    }
    free(temp);

}

void vecstack(struct file *filearray, int *file_count, char *vec1, char *vec2, char *direction, char *matName, FILE *pFile) {
    int i;
    int index1;
    int index2;
    int j;

    bool check=false;
    for(i=0;i<*file_count;i++){
        if(!strcmp(filearray[i].name,matName)){
            check=true;
            break;
        }
    }
    if(check==false){
            for (i = 0; i < *file_count; i++) {
                if (!strcmp(filearray[i].name, vec1)) {
                    index1 = i;
                    break;
                }
            }
            for (i = 0; i < *file_count; i++) {
                if (!strcmp(filearray[i].name, vec2)) {
                    index2 = i;
                    break;
                }
            }
            if (!strcmp(direction, "row")) {
                    if(filearray[index1].row==filearray[index2].row){
                        filearray[*file_count].array = (int **) malloc(2 * sizeof(int *));
                        for (i = 0; i < 2; i++) {
                            filearray[*file_count].array[i] = (int *) malloc(filearray[index1].row * sizeof(int));
                        }
                        filearray[*file_count].name = (char *) malloc(strlen(matName) * sizeof(char)+1);
                        strcpy(filearray[*file_count].name, matName);
                        filearray[*file_count].row = filearray[index1].row;
                        filearray[*file_count].column = 2;
                        for (j = 0; j < filearray[*file_count].row; j++) {
                            filearray[*file_count].array[0][j] = filearray[index1].array[j];
                        }

                        for (j = 0; j < filearray[*file_count].row; j++) {
                            filearray[*file_count].array[1][j] = filearray[index2].array[j];
                        }
                        fprintf(pFile, "vectors concatenated  %s %d %d\n", filearray[*file_count].name, filearray[*file_count].column,
                                filearray[*file_count].row);
                        for (i = 0; i < filearray[*file_count].column; i++) {
                            for (j = 0; j < filearray[*file_count].row; j++) {
                                fprintf(pFile, "%d ", filearray[*file_count].array[i][j]);
                            }
                            fprintf(pFile, "\n");
                        }
                        *file_count = *file_count + 1;

                    }else{
                        fprintf(pFile,"error\n");
                    }



            } else {
                if(filearray[index1].row==filearray[index2].row){
                    filearray[*file_count].array = (int **) malloc(filearray[index1].row * sizeof(int *));


                    for (i = 0; i < filearray[index1].row; i++) {
                        filearray[*file_count].array[i] = (int *) malloc(2 * sizeof(int));
                    }
                    filearray[*file_count].name = (char *) malloc(strlen(matName) * sizeof(char)+1);
                    strcpy(filearray[*file_count].name, matName);
                    filearray[*file_count].column = filearray[index1].row;
                    filearray[*file_count].row = 2;
                    for (j = 0; j < filearray[*file_count].column; j++) {
                        filearray[*file_count].array[j][0] = filearray[index1].array[j];
                    }
                    for (j = 0; j < filearray[*file_count].column; j++) {
                        filearray[*file_count].array[j][1] = filearray[index2].array[j];
                    }
                    fprintf(pFile, "vectors concatenated  %s %d %d\n", filearray[*file_count].name, filearray[*file_count].column,
                            filearray[*file_count].row);
                    for (i = 0; i < filearray[*file_count].column; i++) {
                        for (j = 0; j < filearray[*file_count].row; j++) {
                            fprintf(pFile, "%d ", filearray[*file_count].array[i][j]);
                        }
                        fprintf(pFile, "\n");
                    }
                    *file_count = *file_count + 1;

                }else{
                    fprintf(pFile,"error\n");
                }




            }




    }
    else{
        fprintf(pFile,"error\n");
    }




}

void matstack(struct file *filearray, int *file_count, char *matrix1, char *matrix2, char *direction, int **copy,
              FILE *pFile) {
    int i;
    int j;
    int x = 0;
    int index1;
    int index2;
    int oldColumn;
    int oldRow;
    for (i = 0; i < *file_count; i++) {
        if (!strcmp(filearray[i].name, matrix1)) {
            index1 = i;
            break;
        }
    }

    for (i = 0; i < *file_count; i++) {
        if (!strcmp(filearray[i].name, matrix2)) {
            index2 = i;
            break;
        }
    }
    oldColumn = filearray[index1].column;
    oldRow = filearray[index1].row;
    if (!strcmp(direction, "d")) {
        if (filearray[index1].row == filearray[index2].row) {
            //copy
            for (i = 0; i < oldColumn; i++) {
                for (j = 0; j < oldRow; j++) {
                    copy[i][j] = filearray[index1].array[i][j];
                }
            }
            //free
            for (i = 0; i < oldColumn; i++) {
                free(filearray[index1].array[i]);
            }
            free(filearray[index1].array);
            //resize
            filearray[index1].column = filearray[index1].column * 2;
            filearray[index1].array = (int **) malloc(filearray[index1].column * sizeof(int *));
            for (i = 0; i < filearray[index1].column; i++) {
                filearray[index1].array[i] = (int *) malloc(filearray[index1].row * sizeof(int));
            }
            //copy
            for (i = 0; i < oldColumn; i++) {
                for (j = 0; j < oldRow; j++) {
                    filearray[index1].array[i][j] = copy[i][j];
                }
            }

            for (i = filearray[index2].column; i < filearray[index1].column; i++) {
                for (j = 0; j < filearray[index1].row; j++) {
                    filearray[index1].array[i][j] = filearray[index2].array[x][j];
                }
                x = x + 1;
            }
            fprintf(pFile, "matrices concatenated %s %d %d \n", filearray[index1].name, filearray[index1].column,
                    filearray[index1].row);
            for (i = 0; i < filearray[index1].column; i++) {
                for (j = 0; j < filearray[index1].row; j++) {
                    fprintf(pFile, "%d ", filearray[index1].array[i][j]);
                }
                fprintf(pFile, "\n");
            }

        } else {
            fprintf(pFile, "error\n");
        }

    } else {
        if (filearray[index1].column == filearray[index2].column) {
            //copy
            for (i = 0; i < oldColumn; i++) {
                for (j = 0; j < oldRow; j++) {
                    copy[i][j] = filearray[index1].array[i][j];
                }
            }
            //free
            for (i = 0; i < oldColumn; i++) {
                free(filearray[index1].array[i]);
            }
            free(filearray[index1].array);
            //resize
            filearray[index1].row = filearray[index1].row + filearray[index2].row;
            filearray[index1].array = (int **) malloc(filearray[index1].column * sizeof(int *));
            for (i = 0; i < filearray[index1].column; i++) {
                filearray[index1].array[i] = (int *) malloc(filearray[index1].row * sizeof(int));
            }
            //copy
            for (i = 0; i < oldColumn; i++) {
                for (j = 0; j < oldRow; j++) {
                    filearray[index1].array[i][j] = copy[i][j];
                }
            }


            x = 0;
            for (i = 0; i < filearray[index1].column; i++) {
                for (j = oldRow; j < filearray[index1].row; j++) {
                    filearray[index1].array[i][j] = filearray[index2].array[i][x];
                    x = x + 1;
                }
                x = 0;
            }
            fprintf(pFile, "matrices concatenated %s %d %d \n", filearray[index1].name, filearray[index1].column,
                    filearray[index1].row);
            for (i = 0; i < filearray[index1].column; i++) {
                for (j = 0; j < filearray[index1].row; j++) {
                    fprintf(pFile, "%d ", filearray[index1].array[i][j]);
                }
                fprintf(pFile, "\n");
            }


        } else {
            fprintf(pFile, "error\n");
        }

    }

}

void mvstack(struct file *filearray, int *file_count, char *matName, char *vecName, char *direction, int **copy,
             FILE *pFile) {
    int i;
    int j;
    int index1;
    int index2;
    int oldColumn;
    int oldRow;
    for (i = 0; i < *file_count; i++) {
        if (!strcmp(filearray[i].name, matName)) {
            index1 = i;
            break;
        }
    }

    for (i = 0; i < *file_count; i++) {
        if (!strcmp(filearray[i].name, vecName)) {
            index2 = i;
            break;
        }
    }
    oldColumn = filearray[index1].column;
    oldRow = filearray[index1].row;
    if (!strcmp(direction, "d")) {

        if (filearray[index1].row == filearray[index2].row) {

            //copy
            for (i = 0; i < oldColumn; i++) {
                for (j = 0; j < oldRow; j++) {
                    copy[i][j] = filearray[index1].array[i][j];
                }
            }
            //free
            for (i = 0; i < oldColumn; i++) {
                free(filearray[index1].array[i]);
            }
            free(filearray[index1].array);

            filearray[index1].column = filearray[index1].column + 1;
            //
            filearray[index1].array = (int **) malloc(filearray[index1].column * sizeof(int *));
            for (i = 0; i < filearray[index1].column; i++) {
                filearray[index1].array[i] = (int *) malloc(filearray[index1].row * sizeof(int));
            }
            //
            for (i = 0; i < oldColumn; i++) {
                for (j = 0; j < oldRow; j++) {
                    filearray[index1].array[i][j] = copy[i][j];
                }
            }
            //
            for (i = 0; i < filearray[index1].row; i++) {
                filearray[index1].array[filearray[index1].column - 1][i] = filearray[index2].array[i];
            }
            fprintf(pFile, "matrix and vector concatenated %s %d %d \n", filearray[index1].name, filearray[index1].column,
                    filearray[index1].row);
            for (i = 0; i < filearray[index1].column; i++) {
                for (j = 0; j < filearray[index1].row; j++) {
                    fprintf(pFile, "%d ", filearray[index1].array[i][j]);
                }
                fprintf(pFile, "\n");
            }


        } else {
            fprintf(pFile, "error\n");
        }

    } else {
        //not work true
        if (filearray[index1].column == filearray[index2].row) {

            //copy
            for (i = 0; i < oldColumn; i++) {
                for (j = 0; j < oldRow; j++) {
                    copy[i][j] = filearray[index1].array[i][j];
                }
            }
            //free
            for (i = 0; i < oldColumn; i++) {
                free(filearray[index1].array[i]);
            }
            free(filearray[index1].array);

            filearray[index1].row = filearray[index1].row + 1;
            //
            filearray[index1].array = (int **) malloc(filearray[index1].column * sizeof(int *));
            for (i = 0; i < filearray[index1].column; i++) {
                filearray[index1].array[i] = (int *) malloc(filearray[index1].row * sizeof(int));
            }
            //
            for (i = 0; i < oldColumn; i++) {
                for (j = 0; j < oldRow; j++) {
                    filearray[index1].array[i][j] = copy[i][j];
                }
            }
            //

            for (i = 0; i < filearray[index2].row; i++) {
                filearray[index1].array[i][filearray[index1].row - 1] = filearray[index2].array[i];
            }
            fprintf(pFile, "matrix and vector concatenated %s %d %d \n", filearray[index1].name, filearray[index1].column,
                    filearray[index1].row);
            for (i = 0; i < filearray[index1].column; i++) {
                for (j = 0; j < filearray[index1].row; j++) {
                    fprintf(pFile, "%d ", filearray[index1].array[i][j]);
                }
                fprintf(pFile, "\n");
            }


        } else {
            fprintf(pFile, "error\n");
        }


    }

}

void pad(struct file *filearray, int *file_count, char *name, int column, int row, char *mode, int **copy, FILE *pFile) {
    int i;
    int j;
    int index1;
    int oldRow;
    int oldColumn;
    int temp;
    for (i = 0; i < *file_count; i++) {
        if (!strcmp(filearray[i].name, name)) {
            index1 = i;
            break;
        }
    }
    oldRow = filearray[index1].row;
    oldColumn = filearray[index1].column;
    //copy
    for (i = 0; i < oldColumn; i++) {
        for (j = 0; j < oldRow; j++) {
            copy[i][j] = filearray[index1].array[i][j];
        }
    }

    //yeniden boyutlandir
    filearray[index1].column = filearray[index1].column + column;
    filearray[index1].row = filearray[index1].row + row;
    for (i = 0; i < oldColumn; i++) {
        free(filearray[index1].array[i]);
    }
    free(filearray[index1].array);
    filearray[index1].array = (int **) malloc(filearray[index1].column * sizeof(int *));
    for (i = 0; i < filearray[index1].column; i++) {
        filearray[index1].array[i] = (int *) malloc(filearray[index1].row * sizeof(int));
    }

    //aktarmak
    for (i = 0; i < oldColumn; i++) {
        for (j = 0; j < oldRow; j++) {
            filearray[index1].array[i][j] = copy[i][j];
        }
    }


    for (i = 0; i < oldColumn; i++) {
        temp = filearray[index1].array[i][0];
        for (j = 0; j < oldRow; j++) {
            if (!strcmp(mode, "maximum")) {
                if (temp < filearray[index1].array[i][j]) {
                    temp = filearray[index1].array[i][j];
                }
            } else {
                if (temp > filearray[index1].array[i][j]) {
                    temp = filearray[index1].array[i][j];
                }
            }


        }
        for (j = oldRow; j < filearray[index1].row; j++) {
            filearray[index1].array[i][j] = temp;
        }
    }
    for (i = 0; i < filearray[index1].row; i++) {
        temp = filearray[index1].array[0][i];
        for (j = 0; j < oldColumn; j++) {
            if (!strcmp(mode, "maximum")) {
                if (temp < filearray[index1].array[j][i]) {
                    temp = filearray[index1].array[j][i];
                }
            } else {
                if (temp > filearray[index1].array[j][i]) {
                    temp = filearray[index1].array[j][i];
                }

            }

        }
        for (j = oldColumn; j < filearray[index1].column; j++) {
            filearray[index1].array[j][i] = temp;
        }
    }
    fprintf(pFile, "matrix paded %s %d %d\n", filearray[index1].name, filearray[index1].column, filearray[index1].row);
    for (i = 0; i < filearray[index1].column; i++) {
        for (j = 0; j < filearray[index1].row; j++) {
            fprintf(pFile, "%d ", filearray[index1].array[i][j]);
        }
        fprintf(pFile, "\n");
    }


}

void
padval(struct file *filearray, int *file_count, char *name, int column, int row, int value, int **copy, FILE *pFile) {

    int i;
    int j;
    int index1;
    int oldRow;
    int oldColumn;
    int temp;
    for (i = 0; i < *file_count; i++) {
        if (!strcmp(filearray[i].name, name)) {
            index1 = i;
            break;
        }
    }

    oldRow = filearray[index1].row;
    oldColumn = filearray[index1].column;
    //copy
    for (i = 0; i < oldColumn; i++) {
        for (j = 0; j < oldRow; j++) {
            copy[i][j] = filearray[index1].array[i][j];
        }
    }

    //yeniden boyutlandir
    filearray[index1].column = filearray[index1].column + column;
    filearray[index1].row = filearray[index1].row + row;
    for (i = 0; i < oldColumn; i++) {
        free(filearray[index1].array[i]);
    }
    free(filearray[index1].array);
    filearray[index1].array = (int **) malloc(filearray[index1].column * sizeof(int *));
    for (i = 0; i < filearray[index1].column; i++) {
        filearray[index1].array[i] = (int *) malloc(filearray[index1].row * sizeof(int));
    }

    //aktarmak
    for (i = 0; i < oldColumn; i++) {
        for (j = 0; j < oldRow; j++) {
            filearray[index1].array[i][j] = copy[i][j];
        }
    }
    //

    for (i = 0; i < oldColumn; i++) {
        for (j = oldRow; j < filearray[index1].row; j++) {
            filearray[index1].array[i][j] = value;
        }
    }
    for (i = 0; i < filearray[index1].row; i++) {
        for (j = oldColumn; j < filearray[index1].column; j++) {

            filearray[index1].array[j][i] = value;
        }
    }
    fprintf(pFile, "matrix paded %s %d %d\n", filearray[index1].name, filearray[index1].column, filearray[index1].row);
    for (i = 0; i < filearray[index1].column; i++) {
        for (j = 0; j < filearray[index1].row; j++) {
            fprintf(pFile, "%d ", filearray[index1].array[i][j]);
        }
        fprintf(pFile, "\n");
    }

}

void vecslice(struct file *filearray, int *file_count, char *name, int start, int stop, char *newName, FILE *pFile) {
    int i;
    int j;
    int index1;
    bool check=false;
    for(i=0;i<*file_count;i++){
        if(!strcmp(filearray[i].name,newName)){
            check=true;
            break;
        }
    }
    if(check==false){
        for (i = 0; i < *file_count; i++) {
            if (!strcmp(filearray[i].name, name)) {
                index1 = i;
                break;
            }
        }
        filearray[*file_count].array = (int **) malloc((stop - start) * sizeof(int *));
        filearray[*file_count].name = (char *) malloc(strlen(newName) * sizeof(char) + 1);
        strcpy(filearray[*file_count].name, newName);
        filearray[*file_count].row = stop - start;
        filearray[*file_count].column = 1;
        j = 0;
        for (i = start; i < stop; i++) {
            filearray[*file_count].array[j] = filearray[index1].array[i];
            j++;
        }
        fprintf(pFile, "vector sliced %s %d\n", filearray[*file_count].name, stop - start);
        for (i = 0; i < filearray[*file_count].row; i++) {
            fprintf(pFile, "%d ", filearray[*file_count].array[i]);
        }
        fprintf(pFile, "\n");


        *file_count = *file_count + 1;

    }else{
        fprintf(pFile,"error\n");
    }



}

void matslice(struct file *filearray, int *file_count, char *name, int y1, int y2, int x1, int x2, char *newName,
              FILE *pFile) {
    //x2-x1 y2-y1 s tun satir
    int i;
    int j;
    int column = 0;
    int row = 0;
    int index1;

    bool check=false;
    for(i=0;i<*file_count;i++){
        if(!strcmp(filearray[i].name,newName)){
            check=true;
            break;
        }
    }
    if(check==false){
        if(x2-x1<=0 || y2-y1<=0){
            fprintf(pFile,"error\n");
        }else{
            for (i = 0; i < *file_count; i++) {
                if (!strcmp(filearray[i].name, name)) {
                    index1 = i;
                    break;
                }
            }

            filearray[*file_count].array = (int **) malloc((x2 - x1) * sizeof(int *));
            for (i = 0; i < (x2 - x1); i++) {
                filearray[*file_count].array[i] = (int *) malloc((y2 - y1) * sizeof(int));
            }
            filearray[*file_count].name = (char *) malloc(strlen(newName) * sizeof(char)+1);
            strcpy(filearray[*file_count].name, newName);
            filearray[*file_count].row = y2 - y1;
            filearray[*file_count].column = x2 - x1;
            for (i = x1; i < x2; i++) {
                for (j = y1; j < y2; j++) {
                    filearray[*file_count].array[column][row] = filearray[index1].array[i][j];
                    row++;
                }
                row = 0;
                column++;
            }
            fprintf(pFile, "matrix sliced %s %d %d\n", newName, filearray[*file_count].column, filearray[*file_count].row);
            for (i = 0; i < filearray[*file_count].column; i++) {
                for (j = 0; j < filearray[*file_count].row; j++) {
                    fprintf(pFile, "%d ", filearray[*file_count].array[i][j]);
                }
                fprintf(pFile, "\n");
            }
            *file_count = *file_count + 1;

        }

    }else{
        fprintf(pFile,"error\n");
    }





}

void matslicecol(struct file *filearray, int *file_count, char *name, int index, int start, int stop, char *newName,
                 FILE *pFile) {
    int i;
    int j;
    int x;
    int index1;
    bool check=false;
    for(i=0;i<*file_count;i++){
        if(!strcmp(filearray[i].name,newName)){
            check=true;
            break;
        }
    }
    if(check==false){
        for (i = 0; i < *file_count; i++) {
            if (!strcmp(filearray[i].name, name)) {
                index1 = i;
                break;
            }
        }
        filearray[*file_count].array = (int **) malloc((stop - start) * sizeof(int *));
        filearray[*file_count].name = (char *) malloc(strlen(newName) * sizeof(char)+1);
        strcpy(filearray[*file_count].name, newName);
        filearray[*file_count].row = stop - start;
        filearray[*file_count].column = 1;
        x = 0;
        for (i = start; i < stop; i++) {
            filearray[*file_count].array[x] = filearray[index1].array[i][index];
            x++;
        }

        fprintf(pFile, "vector sliced %s %d\n", filearray[*file_count].name, stop - start);

        for (i = 0; i < filearray[*file_count].row; i++) {
            fprintf(pFile, "%d ", filearray[*file_count].array[i]);
        }
        fprintf(pFile, "\n");


        *file_count = *file_count + 1;

    }else{
        fprintf(pFile,"error\n");
    }


}

void matslicerow(struct file *filearray, int *file_count, char *name, int index, int start, int stop, char *newName,
                 FILE *pFile) {
    int i;
    int j;
    int x;
    int index1;

    bool check=false;
    for(i=0;i<*file_count;i++){
        if(!strcmp(filearray[i].name,newName)){
            check=true;
            break;
        }
    }
    if(check==false){
        for (i = 0; i < *file_count; i++) {
            if (!strcmp(filearray[i].name, name)) {
                index1 = i;
                break;
            }
        }

        filearray[*file_count].array = (int **) malloc((stop - start) * sizeof(int *)+2);
        filearray[*file_count].name = (char *) malloc(strlen(newName) * sizeof(char)+1);
        strcpy(filearray[*file_count].name, newName);
        filearray[*file_count].row = stop - start;
        filearray[*file_count].column = 1;
        x = 0;
        for (i = start; i < stop; i++) {
            filearray[*file_count].array[x] = filearray[index1].array[index][i];
            x++;
        }
        fprintf(pFile, "vector sliced %s %d\n", filearray[*file_count].name, stop - start);
        for (i = 0; i < filearray[*file_count].row; i++) {
            fprintf(pFile, "%d ", filearray[*file_count].array[i]);
        }
        fprintf(pFile, "\n");


        *file_count = *file_count + 1;

    }else{
        fprintf(pFile,"error\n");
    }


}

void add(struct file *filearray, int *file_count, char *matrix1, char *matrix2, FILE *pFile) {
    int i;
    int j;
    int index1;
    int index2;
    for (i = 0; i < *file_count; i++) {
        if (!strcmp(filearray[i].name, matrix1)) {
            index1 = i;
            break;
        }
    }

    for (i = 0; i < *file_count; i++) {
        if (!strcmp(filearray[i].name, matrix2)) {
            index2 = i;
            break;
        }
    }
    if (filearray[index1].column == filearray[index2].column & filearray[index1].row == filearray[index2].row) {
        for (i = 0; i < filearray[index1].column; i++) {
            for (j = 0; j < filearray[index2].row; j++) {
                filearray[index1].array[i][j] = filearray[index1].array[i][j] + filearray[index2].array[i][j];
            }
        }
        fprintf(pFile, "add %s %s  \n", filearray[index1].name, filearray[index2].name);
        for (i = 0; i < filearray[index1].column; i++) {
            for (j = 0; j < filearray[index1].row; j++) {
                fprintf(pFile, "%d ", filearray[index1].array[i][j]);
            }
            fprintf(pFile, "\n");
        }


    } else {
        fprintf(pFile, "error\n");
    }


}

void multiply(struct file *filearray, int *file_count, char *matrix1, char *matrix2, int **copy, FILE *pFile) {
    int i;
    int j;
    int index1;
    int index2;
    for (i = 0; i < *file_count; i++) {
        if (!strcmp(filearray[i].name, matrix1)) {
            index1 = i;
            break;
        }
    }

    for (i = 0; i < *file_count; i++) {
        if (!strcmp(filearray[i].name, matrix2)) {
            index2 = i;
            break;
        }
    }
    if (filearray[index1].column == filearray[index2].column & filearray[index1].row == filearray[index2].row) {
        for (i = 0; i < filearray[index1].column; i++) {
            for (j = 0; j < filearray[index2].row; j++) {
                filearray[index1].array[i][j] = filearray[index1].array[i][j] * filearray[index2].array[i][j];
            }
        }
        fprintf(pFile, "multiply %s %s  \n", filearray[index1].name, filearray[index2].name);
        for (i = 0; i < filearray[index1].column; i++) {
            for (j = 0; j < filearray[index1].row; j++) {
                fprintf(pFile, "%d ", filearray[index1].array[i][j]);
            }
            fprintf(pFile, "\n");
        }


    } else {
        fprintf(pFile, "error\n");
    }

}

void subtract(struct file *filearray, int *file_count, char *matrix1, char *matrix2, FILE *pFile) {
    int i;
    int j;
    int index1;
    int index2;
    for (i = 0; i < *file_count; i++) {
        if (!strcmp(filearray[i].name, matrix1)) {
            index1 = i;
            break;
        }
    }

    for (i = 0; i < *file_count; i++) {
        if (!strcmp(filearray[i].name, matrix2)) {
            index2 = i;
            break;
        }
    }
    if (filearray[index1].column == filearray[index2].column & filearray[index1].row == filearray[index2].row) {
        for (i = 0; i < filearray[index1].column; i++) {
            for (j = 0; j < filearray[index2].row; j++) {
                filearray[index1].array[i][j] = filearray[index1].array[i][j] - filearray[index2].array[i][j];
            }
        }
        fprintf(pFile, "subtract %s %s  \n", filearray[index1].name, filearray[index2].name);
        for (i = 0; i < filearray[index1].column; i++) {
            for (j = 0; j < filearray[index1].row; j++) {
                fprintf(pFile, "%d ", filearray[index1].array[i][j]);
            }
            fprintf(pFile, "\n");
        }


    } else {
        fprintf(pFile, "error\n");
    }

}

void readCommand(char *v[], struct file *filearray, int *file_count, int **copy, FILE *pFile) {
    FILE *fp1;
    char *word = (char *) malloc(25 * sizeof(char));
    char *str1 = (char *) malloc(25 * sizeof(char));
    char *str2 = (char *) malloc(25 * sizeof(char));
    char *str3 = (char *) malloc(25 * sizeof(char));
    char *str4 = (char *) malloc(25 * sizeof(char));
    int int1;
    int int2;
    int int3;
    int int4;
    int c;
    fp1 = fopen(v[1], "r");
    do {
        c = fscanf(fp1, "%s", word);
        if (!strcmp(word, "veczeros")) {
            c = fscanf(fp1, "%s", word);
            strcpy(str1, word);                //str1 name
            c = fscanf(fp1, "%s", word);
            int1 = atoi(word);                //int1 length
            veczeros(filearray, file_count, str1, int1, pFile);


        } else if (!strcmp(word, "matzeros")) {
            c = fscanf(fp1, "%s", word);
            strcpy(str1, word);                //str1 name
            c = fscanf(fp1, "%s", word);
            int1 = atoi(word);                //int1 x
            c = fscanf(fp1, "%s", word);
            int2 = atoi(word);                //int2 y
            matzeros(filearray, file_count, str1, int1, int2, pFile);
        } else if (!strcmp(word, "vecread")) {
            c = fscanf(fp1, "%s", word);
            strcpy(str1, word);                //str1 filename
            vecread(filearray, &v[0], file_count, str1,pFile);

        } else if (!strcmp(word, "matread")) {
            c = fscanf(fp1, "%s", word);
            strcpy(str1, word);                //str1 filename
            matread(filearray, &v[0], file_count, str1, pFile);

        } else if (!strcmp(word, "vecstack")) {
            c = fscanf(fp1, "%s", word);
            strcpy(str1, word);                //str1 vector1name
            c = fscanf(fp1, "%s", word);
            strcpy(str2, word);                //str2 vector2name
            c = fscanf(fp1, "%s", word);
            strcpy(str3, word);                //direction
            c = fscanf(fp1, "%s", word);
            strcpy(str4, word);                //matrix
            vecstack(filearray, file_count, str1, str2, str3, str4, pFile);
        } else if (!strcmp(word, "matstack")) {
            c = fscanf(fp1, "%s", word);
            strcpy(str1, word);                //str1 matrix1name
            c = fscanf(fp1, "%s", word);
            strcpy(str2, word);                //str2 matrix2name
            c = fscanf(fp1, "%s", word);
            strcpy(str3, word);                //where
            matstack(filearray, file_count, str1, str2, str3, copy, pFile);
        } else if (!strcmp(word, "mvstack")) {
            c = fscanf(fp1, "%s", word);
            strcpy(str1, word);                //str1 matrixname
            c = fscanf(fp1, "%s", word);
            strcpy(str2, word);                //str2 vectorname
            c = fscanf(fp1, "%s", word);
            strcpy(str3, word);                //where
            mvstack(filearray, file_count, str1, str2, str3, copy, pFile);
        } else if (!strcmp(word, "pad")) {
            c = fscanf(fp1, "%s", word);
            strcpy(str1, word);                //str1 matrix1name
            c = fscanf(fp1, "%s", word);
            int1 = atoi(word);                //x
            c = fscanf(fp1, "%s", word);
            int2 = atoi(word);                //y
            c = fscanf(fp1, "%s", word);
            strcpy(str2, word);                //mod
            pad(filearray, file_count, str1, int1, int2, str2, copy, pFile);
        } else if (!strcmp(word, "padval")) {
            c = fscanf(fp1, "%s", word);
            strcpy(str1, word);                //matrix name
            c = fscanf(fp1, "%s", word);
            int1 = atoi(word);                //x
            c = fscanf(fp1, "%s", word);
            int2 = atoi(word);                //y
            c = fscanf(fp1, "%s", word);
            int3 = atoi(word);                //val
            padval(filearray, file_count, str1, int1, int2, int3, copy, pFile);
        } else if (!strcmp(word, "vecslice")) {
            c = fscanf(fp1, "%s", word);
            strcpy(str1, word);                //vector name
            c = fscanf(fp1, "%s", word);
            int1 = atoi(word);                //start index
            c = fscanf(fp1, "%s", word);
            int2 = atoi(word);                //stop index
            c = fscanf(fp1, "%s", word);
            strcpy(str2, word);                //elements of vector name
            vecslice(filearray, file_count, str1, int1, int2, str2, pFile);

        } else if (!strcmp(word, "matslicecol")) {
            c = fscanf(fp1, "%s", word);
            strcpy(str1, word);                //matrix name
            c = fscanf(fp1, "%s", word);
            int1 = atoi(word);                //index
            c = fscanf(fp1, "%s", word);
            int2 = atoi(word);                //start
            c = fscanf(fp1, "%s", word);
            int3 = atoi(word);                //stop
            c = fscanf(fp1, "%s", word);
            strcpy(str2, word);                //name
            matslicecol(filearray, file_count, str1, int1, int2, int3, str2, pFile);
        } else if (!strcmp(word, "matslicerow")) {
            c = fscanf(fp1, "%s", word);
            strcpy(str1, word);                //matrix name
            c = fscanf(fp1, "%s", word);
            int1 = atoi(word);                //index
            c = fscanf(fp1, "%s", word);
            int2 = atoi(word);                //start
            c = fscanf(fp1, "%s", word);
            int3 = atoi(word);                //stop
            c = fscanf(fp1, "%s", word);
            strcpy(str2, word);                //name
            matslicerow(filearray, file_count, str1, int1, int2, int3, str2, pFile);
        } else if (!strcmp(word, "matslice")) {
            c = fscanf(fp1, "%s", word);
            strcpy(str1, word);                //matrix name
            c = fscanf(fp1, "%s", word);
            int1 = atoi(word);                //y1
            c = fscanf(fp1, "%s", word);
            int2 = atoi(word);                //y2
            c = fscanf(fp1, "%s", word);
            int3 = atoi(word);                //x1
            c = fscanf(fp1, "%s", word);
            int4 = atoi(word);                //x2
            c = fscanf(fp1, "%s", word);
            strcpy(str2, word);                //name
            matslice(filearray, file_count, str1, int1, int2, int3, int4, str2, pFile);

        } else if (!strcmp(word, "add")) {
            c = fscanf(fp1, "%s", word);
            strcpy(str1, word);                //matrix1
            c = fscanf(fp1, "%s", word);
            strcpy(str2, word);                //matrix2
            add(filearray, file_count, str1, str2, pFile);
        } else if (!strcmp(word, "multiply")) {
            c = fscanf(fp1, "%s", word);
            strcpy(str1, word);                //matrix1
            c = fscanf(fp1, "%s", word);
            strcpy(str2, word);                //matrix2
            multiply(filearray, file_count, str1, str2, copy, pFile);
        } else if (!strcmp(word, "subtract")) {
            c = fscanf(fp1, "%s", word);
            strcpy(str1, word);                //matrix1
            c = fscanf(fp1, "%s", word);
            strcpy(str2, word);                //matrix2
            subtract(filearray, file_count, str1, str2, pFile);
        } else {
            if (fscanf(fp1, "%s", word) != EOF) {
                char ch;
                do {
                    ch = getc(fp1);
                } while (ch != '\n');
                fprintf(pFile, "error\n");


            }


        }
    } while (c != EOF);

    free(word);
    free(str1),
            free(str2);
    free(str3);
    free(str4);
    fclose(fp1);
}


int main(int c, char *v[]) {
    //v1 arrays v2 commands
    FILE *pFile;
    int i;
    int j;
    int file_count = 0;
    int **copy = (int **) malloc(50 * sizeof(int *));
    for (i = 0; i < 50; i++) {
        copy[i] = (int *) malloc(50 * sizeof(int *));
    }
    struct file *filearray = (struct file *) malloc(100 * (sizeof(struct file)));
    pFile=fopen(v[3],"a");
    readCommand(&v[1], filearray, &file_count, copy, pFile);
    //free
    for (i = 0; i < 50; i++) {
        free(copy[i]);
    }
    free(copy);
    for (i = 0; i < file_count; i++) {
        if (filearray[i].column == 1) {
            free(filearray[i].array);
        } else {
            for (j = 0; j < filearray[i].column; j++) {
                free(filearray[i].array[j]);
            }
            free(filearray[i].array);

        }

        free(filearray[i].name);
    }
    free(filearray);
    fclose(pFile);
    return 0;


}
