#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <locale.h>
#include <conio.h>
#include <time.h>
#define MAX 100


typedef struct teacher{
	
	char name[MAX];
	char surname[MAX];
	char title[MAX];
	char teacher_id[MAX];
	
}TEACHER;

typedef struct lecture{
	char code[MAX];
	char name[MAX];
	int credit;
	int taken_student;
	int limit;
	char teacher_id[MAX];
	
}LECTURE;

typedef struct student{
	int id;
	char name[MAX];
	char surname[MAX];
	int taken_lecture;
	int taken_credit;
	
}STUDENT;

typedef struct registration{
	int reg_id;
	int student_id;
	char lecture_id[MAX];
	int statue;
	char date[MAX];
	
}REG;


void add_registration();
void delete_registered_lecture();
void delete_teacher();
void delete_lecture();
void delete_student();
void add_lecture();
void add_student();
void add_teacher();
void print_derkodu_siniflistesi();
void print_teacher();
void print_lecture();
void print_student();

int main (){ 
	
	setlocale(LC_ALL,"Turkish");
	int choice=0;
	while(choice!=13){
		printf(" 1-ADD LECTURE\n 2-REMOVE LECTURE\n 3-ADD TEACHER\n 4-REMOVE TEACHER\n 5-ADD STUDENT\n 6-REMOVE STUDENT\n 7-REGISTER A LECTURE\n 8-DELETE TAKEN LECTURE\n 9-SHOW TEACHER'S LECTURE\n 10-SHOW STUDENT'S TAKEN LECTURES\n 11-SHOW LECTURE'S STUDENT\n 12-DERSKODU_SINIF.txt FILE\n 13-EXIT\n");
		scanf("%d",&choice);
		switch(choice){
			case 1: add_lecture();
			break;
			
			case 2: delete_lecture();
			break;
			
			case 3: add_teacher();
			break;
			
			case 4: delete_teacher();
			break;
			
			case 5: add_student();
			break;
			
			case 6: delete_student();
			break;
			
			case 7: add_registration();
			break;
			
			case 8: delete_registered_lecture();
			break;
			
			case 9: print_teacher();
			break;
			
			case 10: print_student();
			break;
			
			case 11: print_lecture();
			break;
			
			case 12:print_derkodu_siniflistesi();
			break;

		}
	}
	
    return 0; 
} 

int count_lines_lecture(){
	
    FILE *fp = fopen("Lectures.txt", "r");
    if(fp == NULL){
        printf("File can not opened...\n");
        return -1;
    }
    
    int line_count = 0;
    char *line = (char*) malloc(MAX * sizeof(char));
    
    while(fgets(line, MAX, fp) != NULL){
            line_count++;
    }
    
    fclose(fp);
	free(line);
    return line_count;
}

int count_lines_teacher(){
	
    FILE *fp = fopen("Teachers.txt", "r");
    if(fp == NULL){
        printf("File can not opened...\n");
        return -1;
    }
    
    int line_count = 0;
    char *line = (char*) malloc(MAX * sizeof(char));
    
    while(fgets(line, MAX, fp) != NULL){
            line_count++;
    }
    
    fclose(fp);
	free(line);
    return line_count;
}

int count_lines_student(){
	
    FILE *fp = fopen("Students.txt", "r");
    if(fp == NULL){
        printf("File can not opened...\n");
        return -1;
    }
    
    int line_count = 0;
    char *line = (char*) malloc(MAX * sizeof(char));
    
    while(fgets(line, MAX, fp) != NULL){
            line_count++;
    }
    
    fclose(fp);
	free(line);
    return line_count;
}

int count_lines_reg(){
	
    FILE *fp = fopen("Registration.txt", "r");
    if(fp == NULL){
        printf("File can not opened...\n");
        return -1;
    }
    
    int line_count = 0;
    char *line = (char*) malloc(MAX * sizeof(char));
    
    while(fgets(line, MAX, fp) != NULL){
            line_count++;
    }
    
    fclose(fp);
	free(line);
    return line_count;
}

LECTURE *read_lectures(){
    FILE *fp = fopen("Lectures.txt", "r");
    if(fp == NULL){
        printf("File could not be opened...\n");
        return NULL;
    }

    char line[MAX];
    int i;

    LECTURE *lecture_array = (LECTURE*) malloc( count_lines_lecture() * sizeof(LECTURE));

    fseek(fp, 0, SEEK_SET);

    for(i=0; i<count_lines_lecture(); i++){
        fgets(line, MAX, fp);
        sscanf(line, "%s %s %d %d %d %s", lecture_array[i].code, lecture_array[i].name, &lecture_array[i].credit, &lecture_array[i].taken_student,&lecture_array[i].limit,lecture_array[i].teacher_id);
    }

    fclose(fp);
    return lecture_array;
}

TEACHER *read_teacher(){
    FILE *fp = fopen("Teachers.txt", "r");
    if(fp == NULL){
       printf("File could not be opened...\n");
        return NULL;
    }

    char line[MAX];
    int i;

    TEACHER *teacher_arr = (TEACHER*) malloc( count_lines_teacher() * sizeof(TEACHER));

    fseek(fp, 0, SEEK_SET);

    for(i=0; i<count_lines_teacher(); i++){
        fgets(line, MAX, fp);
        sscanf(line,"%s %s %s %s",teacher_arr[i].name,teacher_arr[i].surname,teacher_arr[i].title, teacher_arr[i].teacher_id);
    }


    fclose(fp);
    return teacher_arr;
}

STUDENT *read_student(){
    FILE *fp = fopen("Students.txt", "r");
    if(fp == NULL){
        printf("File could not be opened...\n");
        return NULL;
    }
    
    char line[MAX];
    int i;
    
    STUDENT *student_arr = (STUDENT*) malloc( count_lines_student() * sizeof(STUDENT));
    
    fseek(fp, 0, SEEK_SET);
    
    for(i=0; i<count_lines_student(); i++){
        fgets(line, MAX, fp);
        sscanf(line, "%d %s %s %d %d",&student_arr[i].id,student_arr[i].name,student_arr[i].surname, &student_arr[i].taken_lecture,&student_arr[i].taken_credit);
    }
    
    
    fclose(fp);
    return student_arr;
}

REG *read_reg(){
    FILE *fp = fopen("Registration.txt", "r");
    if(fp == NULL){
       printf("File could not be opened...\n");
        return NULL;
    }

    char line[MAX];
    int i;

    REG *reg_arr = (REG*) malloc( count_lines_reg() * sizeof(REG));

    fseek(fp, 0, SEEK_SET);

    for(i=0; i<count_lines_reg(); i++){
        fgets(line, MAX, fp);
        sscanf(line, "%d %d %s %d %[^\n]s",&reg_arr[i].reg_id,&reg_arr[i].student_id,reg_arr[i].lecture_id,&reg_arr[i].statue,reg_arr[i].date);
    }

    fclose(fp);
    return reg_arr;
}

void add_registration(){
	FILE *fp;
	REG *data_reg = read_reg();
	
	if(data_reg == NULL){
		return;
	}
	STUDENT *data_student = read_student();
	if(data_student == NULL){
		return;
	}
	LECTURE *data_lecture = read_lectures();
	if(data_lecture == NULL){
		return;
	}
	
	REG *new_reg = (REG*) malloc(sizeof(REG));
	int line_reg = count_lines_reg();
	int line_student = count_lines_student();
	int line_lecture = count_lines_lecture();
	char *line = (char*) malloc(MAX * sizeof(char));
	int i, student_index, lecture_index;
	
	printf("Enter student number:\n");
	scanf("%d", &new_reg->student_id);
	
	i = 0;
	while(i<line_student && new_reg->student_id!=data_student[i].id){
		i++;
	}
	if(i == line_student){
		printf("Student could not be found...\n");
		free(line); 
		free(new_reg); 
		free(data_lecture); 
		free(data_reg); 
		free(data_student);
		return;
	}
	student_index = i;
	
	printf("Enter lecture code:\n");
	scanf("%s", new_reg->lecture_id);
	
	i = 0;
	while(i<line_lecture && strcmp(new_reg->lecture_id, data_lecture[i].code) != 0){
		i++;
	}
	if(i == line_lecture){
		printf("Not registred...\n");
		free(line); free(new_reg); free(data_lecture); free(data_reg); free(data_student);
		return;
	}
	lecture_index = i;
	
	i = 0;
	while((i<line_reg) && !((strcmp(new_reg->lecture_id, data_reg[i].lecture_id) == 0) && (new_reg->student_id==data_reg[i].student_id))){
		i++;
	}
	if(i != line_reg){
		
		strcpy(data_reg[i].date,__DATE__);
		data_reg[i].statue=1;
		fp = fopen("Registration.txt", "w");
		for(i=0;i<line_reg;i++){
			fprintf(fp, "\n%d %d %s %d %s", data_reg[i].reg_id, data_reg[i].student_id, data_reg[i].lecture_id,data_reg[i].statue,data_reg[i].date);
		}
		
		fclose(fp);
		printf("Already exist...\n");
		free(line); 
		free(new_reg);
		free(data_lecture); 
		free(data_reg); 
		free(data_student);
		return;
	}
	
	
	fp = fopen("Registration.txt", "a");
	if(line_reg==0){
		new_reg->reg_id=1;
	}
	else{
		new_reg->reg_id=data_reg[line_reg - 1].reg_id + 1;
	}
	
	fprintf(fp, "\n%d %d %s %d %s", new_reg->reg_id, new_reg->student_id, new_reg->lecture_id, 1, __DATE__);
	fclose(fp);
	
	data_student[student_index].taken_lecture++;
	data_student[student_index].taken_credit += data_lecture[lecture_index].credit;
	fp = fopen("Students.txt", "w");
	for(i=0; i<line_student; i++){
		fprintf(fp, "\n%d %s %s %d %d", data_student[i].id, data_student[i].name, data_student[i].surname, data_student[i].taken_credit, data_student[i].taken_lecture);
	}
	fclose(fp);
	free(line); 
	free(new_reg); 
	free(data_lecture); 
	free(data_reg); 
	free(data_student);
	printf("Data is stored successfully...\n");
}

void delete_registered_lecture(){
	
	LECTURE *data_lecture=read_lectures();
	if(data_lecture==NULL){
		return;
	}
	REG *data_reg=read_reg();
	if(data_reg==NULL){
		return;
	}
	STUDENT *data_student=read_student();
	if(data_student==NULL){
		return;
	}
	int line_reg = count_lines_reg();
	int line_student = count_lines_student();
	int line_lecture = count_lines_lecture();
	char code[MAX];
	int i=0,j,lecture_index;
	printf("Enter the code of lecture you want to delete:\n");
	scanf("%s",code);
	
	while(i<line_lecture && strcmp(code, data_lecture[i].code)!=0){
		i++;
	}
	
	if(i==line_lecture){
		printf("Lecture does not exist...\n");
		free(data_student);
		free(data_reg);
		free(data_lecture);
		return;
	}
	lecture_index=i;
	
	for(i=0;i<line_reg;i++){
		if(strcmp(code, data_reg[i].lecture_id)==0){
			j=0;
			while(j<line_student && data_student[j].id!=data_reg[i].student_id){
				j++;
			}
			if(j!= line_student){
				data_student[j].taken_lecture--;
				data_student[j].taken_credit=data_lecture[lecture_index].credit;
			}
		}
	}
	
	FILE *fp=fopen("Registration.txt","w");
	for(i=0;i<line_reg;i++){
		if(strcmp(code,data_reg[i].lecture_id)!=0){
			fprintf(fp,"%d %d %s %d %s\n",data_reg[i].reg_id,data_reg[i].student_id,data_reg[i].lecture_id,data_reg[i].statue,data_reg[i].date);
		}
	}
	fclose(fp);
	
	fp=fopen("Lectures.txt","w");
	for(i=0;i<line_reg;i++){
		if(strcmp(code,data_lecture[i].code)!=0){
			fprintf(fp,"%s %s %d %d %d %s\n",data_lecture[i].code,data_lecture[i].name,data_lecture[i].credit,data_lecture[i].taken_student,data_lecture[i].limit,data_lecture[i].teacher_id);
		}
	}
	fclose(fp);
	
	fp=fopen("Students.txt","w");
	for(i=0;i<line_student;i++){
			fprintf(fp, "%d %s %s %d %d\n", data_student[i].id, data_student[i].name, data_student[i].surname, data_student[i].taken_credit, data_student[i].taken_lecture);
	}
	fclose(fp);
	free(data_student);
	free(data_reg);
	free(data_lecture);
	
    return ;
    
}

void delete_teacher(){
	
	TEACHER *data_teacher=read_teacher();
	if(data_teacher==NULL){
		return;
	}
	
	int line_teacher = count_lines_teacher();
	char teacher_name[MAX];
	int i=0;
	printf("Enter the name of teacher you want to delete:\n");
	scanf("%s",teacher_name);
	
	while(i<line_teacher && strcmp(teacher_name, data_teacher[i].name)!=0){
		i++;
	}
	
	if(i==line_teacher){
		printf("Teacher does not exist...\n");
		free(data_teacher);
		return;
	}
	
	FILE *fp=fopen("Teachers.txt","w");
	for(i=0;i<line_teacher;i++){
		if(strcmp(teacher_name, data_teacher[i].name)!=0){
			fprintf(fp,"%s %s %s %s\n",data_teacher[i].name,data_teacher[i].surname,data_teacher[i].title,data_teacher[i].teacher_id);
		}
	}
	fclose(fp);
	free(data_teacher);
	printf("Teacher deleted successfully...\n");
    return ;
    
}

void delete_student(){
	
	STUDENT *data_student=read_student();
	if(data_student==NULL){
		return;
	}
	
	int line_student = count_lines_student();
	int student_id;
	int i=0;
	printf("Enter the ID of student you want to delete:\n");
	scanf("%d",&student_id);
	
	while(i<line_student && student_id !=data_student[i].id){
		i++;
	}
	
	if(i==line_student){
		printf("Student does not exist...\n");
		free(data_student);
		return;
	}
	
	FILE *fp=fopen("Students.txt","w");
	for(i=0;i<line_student;i++){
		if(student_id !=data_student[i].id){
			fprintf(fp,"%d %s %s %d %d\n",data_student[i].id,data_student[i].name,data_student[i].surname,data_student[i].taken_credit,data_student[i].taken_lecture);
		}
	}
	fclose(fp);
	
	free(data_student);
	return;
    
}

void delete_lecture(){
	
	LECTURE *data_lecture=read_lectures();
	if(data_lecture==NULL){
		return;
	}
	
	int line_lecture = count_lines_lecture();
	char lecture_code[MAX];
	int i=0;
	printf("Enter the code of lecure you want to delete:\n");
	scanf("%s",lecture_code);
	
	while(i<line_lecture && strcmp(lecture_code, data_lecture[i].code)!=0){
		i++;
	}
	
	if(i==line_lecture){
		printf("Lecture does not exist...\n");
		free(data_lecture);
		return;
	}
	
	FILE *fp=fopen("Lectures.txt","w");
	for(i=0;i<line_lecture;i++){
		if(strcmp(lecture_code, data_lecture[i].code)!=0){
			fprintf(fp,"%s %s %d %d %d %s\n",data_lecture[i].code,data_lecture[i].name,data_lecture[i].credit,data_lecture[i].taken_student,data_lecture[i].limit,data_lecture[i].teacher_id);
		}
	}
	fclose(fp);
	
	free(data_lecture);
	return;
    
}


void add_lecture(){
	
	LECTURE new_lecture;
	printf("Code:\n");
	scanf("%s",new_lecture.code);
	printf("Name:\n");
	scanf("%s",new_lecture.name);
	printf("Credit:\n");
	scanf("%d",&new_lecture.credit);
	printf("Taken Student:\n");
	scanf("%d",&new_lecture.taken_student);
	printf("Limit:\n");
	scanf("%d",&new_lecture.limit);
	printf("Teacher ID:\n");
	scanf("%s",new_lecture.teacher_id);
	
	FILE *fp; 
    fp = fopen ("Lectures.txt", "a"); 
    if (fp == NULL) 
    { 
       printf("Error in saving data...\n");
       return;
    }
    fprintf(fp,"\n%s %s %d %d %d %s",new_lecture.code,new_lecture.name,new_lecture.credit,new_lecture.taken_student,new_lecture.limit,new_lecture.teacher_id);
    printf("Data is stored successfully...\n");
    fclose(fp);
    return;
}


void add_student(){
	
	STUDENT new_student;
	printf("Student number:\n");
	scanf("%d",&new_student.id);
	printf("Name:\n");
	scanf("%s",new_student.name);
	printf("Surname:\n");
	scanf("%s",new_student.surname);
	printf("Taken Lecture number:\n");
	scanf("%d",&new_student.taken_lecture);
	printf("Taken Lecture Credit:\n");
	scanf("%d",&new_student.taken_credit);
	
	FILE *fp; 
    fp = fopen ("Students.txt", "a"); 
    if (fp == NULL) 
    { 
       printf("Error in saving data...\n");
       return ;
    }
    fprintf(fp,"\n%d %s %s %d %d",new_student.id,new_student.name,new_student.surname,new_student.taken_lecture,new_student.taken_credit);
    printf("Data is stored successfully...\n");
    fclose(fp);
    return;
}

void add_teacher(){
	
	TEACHER new_teacher;
	printf("Name:\n");
	scanf("%s",new_teacher.name);
	printf("Surname:\n");
	scanf("%s",new_teacher.surname);
	printf("Title:\n");
	scanf("%s",new_teacher.title);
	printf("Teacher ID:\n");
	scanf("%s",new_teacher.teacher_id);
	
	FILE *fp; 
    fp = fopen ("Teachers.txt", "a"); 
    if (fp == NULL) 
    { 
       printf("Error in saving data...\n");
       return ;
    }
    fprintf(fp,"\n%s %s %s %s",new_teacher.name,new_teacher.surname,new_teacher.title,new_teacher.teacher_id);
    printf("Data is stored successfully...\n");
    fclose(fp);
    return;
}

void print_derkodu_siniflistesi(){

	TEACHER *data_teacher=read_teacher();
	LECTURE *data_lecture = read_lectures();
    REG *data_reg = read_reg();
	
	if(data_teacher == NULL && data_lecture == NULL && data_reg == NULL){
		return;
	}
	int line_teacher = count_lines_teacher();
	int line_reg = count_lines_reg();
	int line_lecture = count_lines_lecture();
	char teacher_id[MAX];
	char lecture_id[MAX];
	char output_file[50];
	int i;
	int teacher_index;

	printf("Enter the ID of teacher:\n");
	scanf("%s",teacher_id);
	
	while(i<line_teacher && strcmp(teacher_id, data_teacher[i].teacher_id) != 0){
		i++;
	}
	
	if(i==line_teacher){
		printf("Teacher does not exist...\n");
		free(data_teacher);
		free(data_lecture);
		free(data_reg);
		return;
	}
	
	teacher_index=i;
	for(i=0; i<line_lecture; i++){
		if(data_lecture[i].teacher_id==teacher_id){
			printf("%s\n",data_lecture[i].code);
		}
	}
	
	printf("Enter lecture code:\n");
	scanf("%s",lecture_id);
	i=0;
	while(i<line_lecture && strcmp(lecture_id, data_lecture[i].code) != 0){
		i++;
	}
	if(i == line_lecture){
		printf("Lecture does not exist...\n");
		free(data_lecture); 
		free(data_reg); 
		free(data_teacher);
		return;
	}
	
	if(strcmp(data_teacher[teacher_index].teacher_id, data_lecture[i].teacher_id) != 0){
		printf("Miss match...\n");
		free(data_lecture); 
		free(data_reg); 
		free(data_teacher);
	}
	
	FILE *fp;
	strcpy(output_file, lecture_id);
	strcat(output_file, "_SINIFLISTESI.txt");
	fp = fopen(output_file, "w");
	for(i=0; i<line_reg; i++){
		if(strcmp(lecture_id, data_reg[i].lecture_id) == 0 && data_reg[i].statue == 1){
			fprintf(fp, "%d\n", data_reg[i].student_id);
		}
	}
    printf("Data is listed successfully...\n");
    fclose(fp);
    free(data_lecture); 
	free(data_reg); 
	free(data_teacher);
	
    return ;
}

void print_teacher(){
	
	LECTURE *data_lecture=read_lectures();
	TEACHER *ptr=read_teacher();
	
	if(ptr == NULL && data_lecture == NULL){
        return;
    }
	
	int line_teacher = count_lines_teacher();
	int line_lecture = count_lines_lecture();
	
	char id[MAX];
	int i=0;
	printf("Enter the ID of teacher:\n");
	scanf("%s",id);
	
	while(i<line_teacher && strcmp(ptr[i].teacher_id,id)!=0){
		i++;
	}
	
	if(i==line_teacher){
		printf("Teacher does not exist...\n");
		free(ptr);
		free(data_lecture);
		return;
	}
	
	
	for(i=0;i<line_lecture;i++){
		if(strcmp(data_lecture[i].teacher_id,id)==0){
			printf("%s\n",data_lecture[i].code);
		}
	}
	
	free(ptr);
	free(data_lecture);
	
    return ;
	
}


void print_lecture(){
	
    LECTURE *data_lecture = read_lectures();
    REG *data_reg = read_reg();
    if(data_reg == NULL && data_lecture == NULL){
        return;
    }
    int line_lecture = count_lines_lecture();
    int line_reg = count_lines_reg();
    int i;
    char code[MAX];
    
    printf("Enter lecture code:\n ");
    scanf("%s", code);
    
    i = 0;
    while(i<line_lecture && strcmp(code, data_lecture[i].code) != 0){
        i++;
    }
    if(i == line_lecture){
        printf("No such lecture...\n");
        free(data_lecture); 
		free(data_reg);
        return;
    }
    
    for(i=0; i<line_reg; i++){
        if(strcmp(code, data_reg[i].lecture_id) == 0){
            printf("%d\n", data_reg[i].student_id);
        }
    }
    
    free(data_lecture);
	free(data_reg);
}


void print_student(){
	
	STUDENT *data_student = read_student();
    REG *data_reg = read_reg();
    if(data_reg == NULL && data_student == NULL){
        return;
    }
    int line_student = count_lines_student();
    int line_reg = count_lines_reg();
    int i;
    int student_id;
    
    printf("Enter student id:\n");
    scanf("%d", &student_id);
    
    i = 0;
    while(i<line_student && (student_id!=data_student[i].id)){
        i++;
    }
    if(i == line_student){
        printf("No such student...\n");
        free(data_student); 
		free(data_reg);
        return;
    }
    
    for(i=0; i<line_reg; i++){
        if(student_id==data_reg[i].student_id){
            printf("%s\n", data_reg[i].lecture_id);
        }
    }
    
    free(data_student);
	free(data_reg);
}

	
























