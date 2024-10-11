#include <stdio.h>
#include <stdlib.h>
#include <math.h>

const int M = 12;
const int N = 11;

void monthly(double sales[12], char months[M][N]){
    FILE* fptr;
    char sale[2][6] = {"Month", "Sale"};
    char content[] = "Monthly Sales Report for 2024";

    fptr = fopen("sales_report.txt", "w");

    fprintf(fptr, "%s\n\n", content);
    fprintf(fptr, "%-10s %s\n", sale[0], sale[1]);

    for (int i = 0; i < 12; i++){
        fprintf(fptr, "%-10s %.2lf\n", months[i], sales[i]);
    }

    fclose(fptr);
}

void summary(double sales[12], char months[M][N]){
    FILE* fptr;
    double min = sales[0];
    int min_index = 0;
    double max = sales[0];
    int max_index = 0;
    double average;
    char content[] = "\nSales summary report:";
    char sale[3][15] = {"Minimum sales:", "Maximum sales:", "Average sales:"};

    fptr = fopen("sales_report.txt", "a");

    for (int i = 0; i < 12; i++){
        if (sales[i] < min){
            min = sales[i];
            min_index = i;
        }
        if (sales[i] > max){
            max = sales[i];
            max_index = i;
        }
        average += sales[i];
    }

    average /= 12;

    fprintf(fptr, "%s\n\n", content);
    fprintf(fptr, "%-16s %.2lf  (%s)\n", sale[0], sales[min_index], months[min_index]);
    fprintf(fptr, "%-16s %.2lf  (%s)\n", sale[1], sales[max_index], months[max_index]);
    fprintf(fptr, "%-16s %.2lf", sale[2], average);

    fclose(fptr);
}

void moving(double sales[12], char months[M][N]){
    FILE* fptr;
    double jan_to_june, feb_to_july, mar_to_aug, apr_to_sep, may_to_oct, june_to_nov, july_to_dec;
    double averages[7];
    char content[] = "\n\nSix-Month moving average report:";
    char combined[20];
    jan_to_june = feb_to_july = mar_to_aug = apr_to_sep = may_to_oct = june_to_nov = july_to_dec = 0;

    fptr = fopen("sales_report.txt", "a");

    for (int i = 0; i < 6; i++){
        jan_to_june += sales[i];
        feb_to_july += sales[i+1];
        mar_to_aug += sales[i + 2];
        apr_to_sep += sales[i + 3];
        may_to_oct += sales[i + 4];
        june_to_nov += sales[i + 5];
        july_to_dec += sales[i + 6];
    }

    averages[0] = roundf((jan_to_june /= 6) * 100) / 100;
    averages[1] = roundf((feb_to_july /= 6) * 100) / 100;
    averages[2] = roundf((mar_to_aug /= 6) * 100) / 100;
    averages[3] = roundf((apr_to_sep /= 6) * 100) / 100;
    averages[4] = roundf((may_to_oct /= 6) * 100) / 100;
    averages[5] = roundf((june_to_nov /= 6) * 100) / 100;
    averages[6] = roundf((july_to_dec /= 6) * 100) / 100;

    fprintf(fptr, "%s\n\n", content);
    for (int k = 0; k < 7; k++){
        sprintf(combined, "%s-%s", months[k], months[k + 5]);
        fprintf(fptr, "%-17s %.2lf\n", combined, averages[k]);
    }

    fclose(fptr);
}

void sorted(double sales[12], char months[M][N]){
    FILE* fptr;
    int i = 0;
    int index[12] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    char content[] = "\nSales report (highest to lowest):";
    char sale[2][6] = {"Month", "Sale"};

    fptr = fopen("sales_report.txt", "a");

    while (i != 11){
        if (sales[i] < sales[i + 1]){
            double temp = sales[i + 1];
            int temp_index = index[i + 1];
            sales[i + 1] = sales[i];
            index[i + 1] = index[i];
            sales[i] = temp;
            index[i] = temp_index;
            i = 0;

        }
        if (sales[i] > sales[i + 1]){
            i++;
        }
    }

    fprintf(fptr, "%s\n\n", content);
    fprintf(fptr, "%-12s %s\n", sale[0], sale[1]);

    for (int k = 0; k < 12; k++){
        fprintf(fptr, "%-12s $%.2lf\n", months[index[k]], sales[k]);
    }
}

int main(){    
    FILE* ptr;
    double sales[12];
    double sale;
    int i = 0;
    char currentline[100];
    char months[M][N] = {"January", "February", "March", "April", "May", "June", 
    "July", "August", "September", "October", "November", "December"};

    ptr = fopen("sales.txt", "r");

    fscanf(ptr, "%lf", &sale);
    sales[i] = sale;
    i++;

    while (fgets(currentline, 12, ptr) != NULL){
        fscanf(ptr, "%lf", &sale);
        sales[i] = sale;
        i++;
    }
    fclose(ptr);

    monthly(sales, months);
    summary(sales, months);
    moving(sales, months);
    sorted(sales, months);

    return 0;
}