#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int **allocate_dynamic_matrix(int , int );
void deallocate_dynamic_matrix(int **, int );
int is_in_colors(char *colors[], char c[10]);
void get_colors(int N, char **selectedColors, int **colorMatrix, char *allcolors[]);
void shift_right(int **matrix, int row, int N);
int is_valid(int **matrix, int row, int N);
void print_colors(int **matrix, int N, char *colors[]);
int backTrack(int **color_grid, char **colors, int N, int row_number, int mod);

int main(){
    char *colors[] = {"pink","white","black","blue","orange","green","yellow","brown"};
    int i;
    int **color_grid;
    char **colors_to_use;
    int N;
    int colorIndex;
    int control;
    int mod;
    printf("Enter size of NxN color grid(3-8): ");
    scanf("%d", &N);
    printf("Please enter running mode for program(0-Normal 1-Detailed): ");
    scanf("%d", &mod);
    while(N>8 || N<3){
        printf("Invalid value. Please enter a value between 3-8: ");
        scanf("%d", &N);
    }
    color_grid = allocate_dynamic_matrix(N, N);
    colors_to_use = (char**) malloc(N*sizeof(char*));
    for(i = 0; i<N; i++){
        colors_to_use[i] = (char*) malloc(10*sizeof (char));
    }

    printf("\nColors available: ");
    for (i = 0; i<8; i++){
        printf(" %s ", colors[i]);
    }
    printf("\nChose %d colors to fill the matrix with: ", N);
    printf("\n");
    for(i = 0; i<N; i++){
        char c[10];
        printf("Color %d: ", i+1);
        scanf("%s", c);
        colorIndex = is_in_colors(colors, c);
        while (colorIndex < 0){
            printf("Please enter a color that is available: ");
            scanf("%s", c);
            colorIndex = is_in_colors(colors, c);
        }
        strcpy(colors_to_use[i], c);
    }
    get_colors(N, colors_to_use, color_grid, colors);
    printf("Initial Color Matrix: \n\n");
    print_colors(color_grid, N, colors);
    control = backTrack(color_grid, colors, N, 0, mod);
    if(control) {
        printf("\n\nProgram was succesful!\n\n");
        printf("Final state of color matrix: \n\n");
        print_colors(color_grid, N, colors);
    }
    else {
        printf("Program failed :(");
    }
    deallocate_dynamic_matrix(color_grid, N);
    return(0);

}

void get_colors(int N, char **selectedColors, int **colorMatrix, char *allcolors[]) {
    int i, j;
    int k = 0;
    char c[10];
    int flag = 0;
    printf("\n");
    printf("Colors you can choose: ");
    for(i = 0; i < N; i++) {
        printf("%s, ", selectedColors[i]);
    }

    printf("\n\n");

    for(i = 0; i < N; i++) {
        for(j = 0; j < N; j++) {
            printf("ENTER MATRIX[%d][%d]:",i,j);
            scanf("%s",c);
            flag = is_in_colors(selectedColors, c);
            while (flag < 0){
                printf("Choose an available color");
                scanf("%s", c);
                flag = is_in_colors(selectedColors, c);
            }
            colorMatrix[i][j] = is_in_colors(allcolors, c);
        }
        printf("\n");
    }
}

int backTrack(int **color_grid, char **colors, int N, int row_number, int mod) {
    int i;
    int control = 0;
    if(row_number >= N) {
        return 1;
    }
    else {
        for(i = 0; i < N; i++) {
            if(is_valid(color_grid, row_number, N) == 1 && control == 0) {
                if(row_number != 0) {
                	if(mod == 1){
                		printf("\nValid Row %d: \n",row_number + 1);
                		printf("Color Matrix\n\n");
                    	print_colors(color_grid, N, colors);
					}
                    
                }
                control = backTrack(color_grid, colors, N, row_number + 1, mod);
            }
            if(i < N-1 && control == 0) {
                shift_right(color_grid, row_number, N);
            }
        }
    }
    return control;
}
void print_colors(int **matrix, int N, char *colors[])
{
    int i,j;
    for(i=0;i<N;i++)
    {
        for(j=0;j<N;j++)
            printf("%s ",colors[matrix[i][j]]);
        printf("\n");
    }
}

int is_valid(int **matrix, int row, int N)
{
    int temp;
    int j=0;
    while(j<N)
    {
        temp=row-1;
        while(temp>=0)
        {
            if(matrix[row][j]==matrix[temp][j])
                return 0;
            temp--;
        }
        j++;
    }
    return 1;
}
void shift_right(int **matrix, int row, int N)
{
    int i,last;
    last=matrix[row][N-1];
    for(i=N-1;i>0;i--)
        matrix[row][i]=matrix[row][i-1];
    matrix[row][0]=last;
}

int is_in_colors(char *colors[], char c[10]){
    int i;
    for(i = 0; i<8; i++){
        if(strcmp(colors[i], c) == 0){
            return i;
        }
    }
    return -1;
}

int **allocate_dynamic_matrix(int row, int col)
{
    int **ret_val;
    int i;

    ret_val = (int **)malloc(sizeof(int *) * row);
    if (ret_val == NULL) {
        perror("memory allocation failure");
        exit(EXIT_FAILURE);
    }

    for (i = 0; i < row; ++i) {
        ret_val[i] = (int *)malloc(sizeof(int) * col);
        if (ret_val[i] == NULL) {
            perror("memory allocation failure");
            exit(EXIT_FAILURE);
        }
    }

    return ret_val;
}

void deallocate_dynamic_matrix(int **matrix, int row)
{
    int i;

    for (i = 0; i < row; ++i) {
        free(matrix[i]);
    }
    free(matrix);
}
