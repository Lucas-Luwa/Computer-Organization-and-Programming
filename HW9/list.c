/**
 * CS 2110 - Fall 2021 - Homework 9
 *
 * @author Lucas Luwa
 *
 * list.c: Complete the functions!
 */

/**
 * !!!!!!!!!!!!!!!!!!!!!!!!!!!!-IMPORTANT-!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 * For any function that must use malloc, if malloc returns NULL, the function
 * itself should return NULL if needs to return something (or return FAILURE if
 * the function returns an int).
 */

// Do not add ANY additional includes!!!
#include "list.h"
#include <stdlib.h>//malloc
#include <stdio.h>//printf

/* You should NOT have any global variables. */

static struct user *create_user(char *name, enum user_type type, union user_data data);
static int create_student(int num_classes, double *grades, struct student *dataOut); //completed for you
static int create_instructor(double salary, struct instructor *dataOut); //completed for you
static int user_equal(const struct user *user1, const struct user *user2);

/** create_user
 *
 * Helper function that creates a struct user by allocating memory for it on the heap
 * and initializing with the passed in data. You MUST create a deep copy of
 * the data union. This means malloc'ing space for copies of each field.
 *
 * If malloc returns NULL, you should return NULL as well.
 *
 * If creating a student/instructor fails, you must free everything you've allocated
 * and return NULL
 *
 * You should call create_student() or create_instructor() in this function
 * to create a deep copy of the union user_data depending on the enum user_type
 *
 * (hint: you cannot just assign the parameter data to the data part of user)
 *
 * Remember to set the next pointer to NULL.
 *
 * @param the fields of the struct user struct
 * @return a struct user, return NULL if malloc fails
 */
static struct user *create_user(char *name, enum user_type type, union user_data data)
{//Please check this to make sure I'm not screwing myself over.
    struct user *myUser = malloc(sizeof(struct user));
    if(!myUser){
        return NULL;
    }
    if(!name){
        myUser->name = NULL;
    }else{
        myUser->name = malloc(strlen(name)+1);
        if (!myUser->name) {
            free(myUser->name);
            return NULL;
        }
        strncpy(myUser->name,name,strlen(name)+1);
    }
    int result; 
    if(type == STUDENT){
        result = create_student(data.student.num_classes, data.student.grades, &myUser->data.student);
    }else if(type == INSTRUCTOR){
        result = create_instructor(data.instructor.salary, &myUser->data.instructor);
    }
    if(result==FAILURE){
        free(myUser);
        return NULL;
    }
    //printf("hi");//nmot in original submission. works:)
    myUser->type = type;
    myUser->next = NULL;
    //myUser->data = data;
    return myUser;
}

/** create_student
 *
 * Helper function that creates a struct student and allocates memory for the grade array on the heap.
 *
 * THIS FUNCTION IS IMPLEMENTED FOR YOU
 *
 * @param the fields of the student struct, and an existing pointer to a student
 * @return FAILURE if malloc fails, SUCCESS otherwise.
 */
static int create_student(int num_classes, double *grades, struct student *dataOut)
{
    /***do not change anything in this function***/
    dataOut->num_classes = num_classes;
    dataOut->grades = NULL;
    if (grades != NULL) {
        if (!(dataOut->grades = (double *) malloc(sizeof(double)*num_classes))) return FAILURE;
        memcpy(dataOut->grades, grades, sizeof(double)*num_classes);
    }
    return SUCCESS;
}

/** create_instructor
 *
 * Helper function that creates an struct instructor.
 *
 * THIS FUNCTION IS IMPLEMENTED FOR YOU
 *
 * @param the fields of the struct instructor, and an existing pointer to an instructor
 * @return always SUCCESS, since there is no malloc call
 */
static int create_instructor(double salary, struct instructor *dataOut)
{
    /***do not edit anything in this function***/
    dataOut->salary = salary; //yes that's all this function does
    return SUCCESS;
}

/** student_equal
 *
 * Helper function to compare two struct students. You may find it useful to call this helper
 * function from the user_equal function that you have to implement.
 *
 * @param the two student structs to be compared
 * @return 1 if equal, 0 otherwise
 */
static int student_equal(const struct student *student1, const struct student *student2)
{
    if (student1->num_classes != student2->num_classes) return 0;
    if (student1->grades != student2->grades)
    {
        if (student1->grades == NULL || student2->grades == NULL) return 0;
        if (memcmp(student1->grades, student2->grades,
                student1->num_classes * sizeof(double)))
        {
            return 0;
        }
    }
    return 1;
}

/** user_equal
 * Helper function to help you compare two user structs.
 *
 * If the name, type, and union fields are all equal, you should return 1.
 * Otherwise, return 0.
 *
 * NOTE: struct members that are pointers may be null!
 * If two users both have null for a certain pointer, the pointers are
 * considered equal.
 * However, if either of the input users is NULL, you should return 0.
 *
 * You may find it useful to call the student_equal function defined above.
 *
 * Make sure you're using the right function when comparing the name.
 * Remember that you are allowed to use functions from string.h
 *
 * This is meant to be used as a helper function in 'contains'; it is not tested
 * by the autograder.
 *
 * @param the two struct user structs to be compared
 * @return 1 if equal, 0 otherwise
 */
static int user_equal(const struct user *user1, const struct user *user2)
{
    int result = 0;
    if(!user1 || !user2|| user1->type != user2->type){
        return 0;
    }
    if(user1->type == INSTRUCTOR){
        if(user1->data.instructor.salary == user2->data.instructor.salary){
            result = 1;
        }
    }else{
        result = student_equal(&user1->data.student, &user2->data.student);
    }
    if(!user1->name && !user2->name) return 1;
    if((!user1->name && user2->name != NULL) || (!user2->name && user1->name != NULL))return 0;
    if(strcmp(user1->name, user2->name)!=0){
        result = 0;
    }
    return result;
}

/** create_list
 *
 * Creates a struct user_list by allocating memory for it on the heap.
 * Be sure to initialize size to zero and head to NULL.
 *
 * If malloc returns NULL, you should return NULL to indicate failure.
 *
 * @return a pointer to a new struct list or NULL on failure
 */
struct user_list *create_list(void)
{
    struct user_list *myList = malloc(sizeof(struct user_list));
    if(!myList){
        free(myList);//was changed by Sir. Kevin
        return NULL;
    }
    myList->size = 0;
    myList->head = NULL;
    return myList;
}

/** push_front
 *
 * Adds the element at the front of the struct user_list.
 *
 * @param list a pointer to the struct user_list structure.
 * @param      the fields of the struct user struct
 * @return FAILURE if the struct user_list is NULL or if allocating the new user fails,
 * SUCCESS if successful.
 */
int push_front(struct user_list *list, char *name, enum user_type type, union user_data data)
{
    if(!list){
        return FAILURE;
    }
    struct user *myUser = create_user(name, type, data);
    if(!myUser){
        return FAILURE;
    }
    myUser->next = list->head; 
    list->head = myUser;//Also Good
    list->size = list->size+1;//Definitely Correct
    return SUCCESS;
}

/** push_back
 *
 * Adds the element to the back of the struct user_list.
 *
 * @param list a pointer to the struct user_list structure.
 * @param      the fields of the struct user struct
 * @return FAILURE if the index is out of bounds or the struct user_list is NULL
 *         or malloc fails (do not add the data in this case)
 *         otherwise return SUCCESS
 */
int push_back(struct user_list *list, char *name, enum user_type type, union user_data data)
{
    if(!list){
        return FAILURE;
    }
    struct user *myUser = create_user(name, type, data);
    if(!myUser){
        return FAILURE;
    }
    struct user *myUser2 = list->head;
    if(list->size==0){
        list->head = myUser;
    }
    else if(list->size>0){
    for(int i = 0;i<list->size-1;i++){
        myUser2 = myUser2->next;
    }
    myUser2->next = myUser;
    }
    list->size = list->size+1;//Definitely Correct
    return SUCCESS;
}

/** add_at_index
 *
 * Add the element at the specified index in the struct user_list. This index must lie in
 * the inclusive range [0,size].
 * For example, if you have no elements in the struct user_list,
 * you should be able to add to index 0 but no further.
 * If you have two elements in the struct user_list,
 * you should be able to add to index 2 but no further.
 *
 * @param list a pointer to the struct user_list structure
 * @param index 0-based, starting from the head in the inclusive range
 *              [0,size]
 * @param the fields of the struct user struct
 * @return FAILURE if the index is out of bounds or the struct user_list is NULL
 *         or malloc fails (do not add the data in this case)
 *         otherwise return SUCCESS
 */
int add_at_index(struct user_list *list, int index, char *name, enum user_type type, union user_data data)
{
    if(!list||index<0 || index> list->size){
        return FAILURE;
    }
    if(index == 0){
        push_front(list, name, type, data);
    }else if(index == list->size){
        push_back(list, name, type, data);
    }else{
        struct user *myUser = create_user(name, type, data);
        if(!myUser){
            return FAILURE;
        }
        struct user *myUser2 = list->head;
        struct user *holder;
        for(int i = 0; i<index-1;i++){
            myUser2 = myUser2->next;
        }
        holder = myUser2->next;
        myUser->next = holder;
        myUser2->next = myUser;
        list->size++;
    }   
    return SUCCESS;
}

/** get
 *
 * Gets the data at the specified index in the struct user_list
 *
 * @param list a pointer to the struct user_list structure
 * @param index 0-based, starting from the head.
 * @param dataOut A pointer to a pointer used to return the data from the
 *        specified index in the struct user_list or NULL on failure.
 * @return FAILURE if dataOut is NULL or index is out of range of the struct user_list or
 *         the struct user_list is NULL, SUCCESS otherwise
 */
int get(struct user_list *list, int index, struct user **dataOut)
{
    if(!list||index >= list->size||index<0){
        return FAILURE;
    }
    if(dataOut == NULL||*dataOut == NULL){
        return FAILURE;
    }
    struct user *myUser =  list->head;

    for(int i = 0;i<index;i++){
        myUser = myUser->next;
    }
    *dataOut = myUser;
    return SUCCESS;
}

/** contains
  *
  * Traverses the struct user_list, trying to see if the struct user_list contains some
  * data. We say the list contains some input if there exists some user with
  * equal data as the input.
  *
  * You should use 'user_equal' here to compare the data. Note that pointers are
  * allowed to be null!
  *
  * If there are multiple pieces of data in the struct user_list which are equal to
  * the "data" parameter, return the one at the lowest index.
  *
  *
  * @param list a pointer to the struct user_list structure
  * @param data The data, to see if it exists in the struct user_list
  * @param dataOut A pointer to a pointer used to return the data contained in
  *                the struct user_list or NULL on failure
  * @return int    FAILURE if dataOut is NULL, the list is NULL, or the list
  *                does not contain data, else SUCCESS
  */
int contains(struct user_list *list, struct user *data, struct user **dataOut)
{
    if(!list){
        *dataOut = NULL;
        return FAILURE;
    }if(!dataOut){
        return FAILURE;
    }
    int found = 0;
    struct user *myUser =  list->head;
    for(int i = 0;i<list->size;i++){
        if(user_equal(data,myUser) && found==0){
            found = 1;
            *dataOut = myUser;
        }
        myUser = myUser->next;
    }
    if(found == 0){
        *dataOut = NULL;
        return FAILURE;
    }
    return SUCCESS;
}

/** pop_front
  *
  * Removes the user at the front of the struct user_list, and returns its data.
  *
  * @param list a pointer to the struct user_list.
  * @param dataOut A pointer to a pointer used to return the data in the first
  *                struct user or NULL if the struct user_list is NULL or empty
  * @return FAILURE if dataOut is NULL (the struct user_list is NULL or empty),
  *         else SUCCESS
  */
int pop_front(struct user_list *list, struct user **dataOut)
{
    if(!dataOut||!list||list->size==0){
        return FAILURE;
    }
    *dataOut = list->head;
    struct user *myUser =  list->head;
    if(list->size>1){
        list->head = myUser->next;
    }
    list->size = list->size-1;
    return SUCCESS;
}

/** pop_back
  *
  * Removes the user at the back of the struct user_list, and returns its data.
  *
  * @param list a pointer to the struct user_list.
  * @param dataOut A pointer to a pointer used to return the data in the last
  *                struct user or NULL if the struct user_list is NULL or empty
  * @return FAILURE if dataOut is NULL (the struct user_list is NULL or empty),
  *         else SUCCESS
  */
int pop_back(struct user_list *list, struct user **dataOut)
{
    if(!dataOut||!list||list->size==0){
        return FAILURE;
    }
    struct user *myUser =  list->head;
    struct user *myUser2 = list->head;
    for(int i = 0;i<list->size-1;i++){
        myUser = myUser->next;
    }
    *dataOut = myUser;
    for(int i = 0;i<list->size-2;i++){
        myUser2 = myUser2->next;
    }
    myUser2->next = NULL;
    list->size = list->size-1;
    return SUCCESS;
}


/** remove_at_index
 *
 * Remove the element at the specified index in the struct user_list.
 *
 * @param list a pointer to the struct user_list structure
 * @param dataOut A pointer to a pointer used to return the data in the 
 *                struct user at index or NULL if the struct user_list is NULL or empty
 * @param index 0-based, starting from the head in the inclusive range
 *              [0,size-1]
 * @return FAILURE if the index is out of bounds, the struct user_list is NULL or
 *         the dataOut is NULL
 *         otherwise return SUCCESS
 */
int remove_at_index(struct user_list *list, struct user **dataOut, int index)
{
    int returnVal = SUCCESS;
    if(!dataOut||!list||list->size==0||index >= list->size||index<0){
        return FAILURE;
    }
    if(index==0 && list->size == 1){
        *dataOut = list->head;
        list->head = NULL;
        list->size = list->size-1;
    }
    else if(index==list->size-1){
        returnVal = pop_back(list, dataOut);
    }else if(index == 0){
        returnVal = pop_front(list, dataOut);
    }
    else{
    struct user *myUser =  list->head;
    struct user *myUser2 = list->head;
    for(int i = 0;i<index;i++){
        myUser = myUser->next;
    }
    *dataOut = myUser;
    for(int i = 0;i<index-1;i++){
        myUser2 = myUser2->next;
    }
    myUser2->next = myUser->next;
    list->size = list->size-1;
    }
    return returnVal;
}

/** empty_list
 *
 * Empties the struct user_list. After this is called, the struct user_list should be
 * empty. This does NOT free the struct user_list struct itself, just all users and
 * data within. Make sure to check that the list is not NULL before
 * using it.
 *
 * Once again, the things that need to be freed after this function are:
 * - the user structs
 * - all pointers in the user struct (and the union within)
 *
 * However, if you're using other functions you've written (which you should be),
 * those functions might take care of some of the freeing for you.
 *
 * You may call free on a char pointer as well as a struct pointer.
 *
 * If 'list' is NULL, don't do anything.
 *
 * @param list a pointer to the struct user_list structure
 */
void empty_list(struct user_list *list)
{
    if(!list)return;
    if(list->head == NULL)return;
    int sizeHolder = list->size;
        for(int i = 0; i<sizeHolder;i++){
            struct user *dataOut;
            pop_back(list, &dataOut);//free 3 for student(name, grades, node), 2 for instructors 
            free(dataOut->name);
            if(dataOut->type == STUDENT){
                free(dataOut->data.student.grades);
            }
            free(dataOut);
        }
        list->head = NULL;  
}

/** get_highest_paid
 *
 * Traverses the struct user_list, determining the highest of all instructor salaries and
 * returning the struct user corresponding to the highest paid instructor.
 *
 * If there are multiple highest paid instructors in the list, return the one that shows up
 * earlier in the list (closer to head).
 *
 * You should make sure your code only looks at instructors, as students do not have salaries!
 *
 * If there are no instructors in the list, place NULL at dataOut.
 *
 * @param list a pointer to the struct user_list structure
 * @param dataOut A pointer to pointer to struct user used to return the highest paid instructor.
 *                  or NULL if there are no instructors or the list is NULL or empty
 * @return FAILURE if the struct user_list is NULL or empty, else SUCCESS
 */
int get_highest_paid(struct user_list *list, struct user **dataOut)
{
    if(!list||list->size == 0){
        *dataOut = NULL;
        return FAILURE;
    }
    int index = 0;
    double prevSalary = 0;
    int instructorCount = 0;
    struct user *myUser =  list->head;
    for(int i = 0; i<list->size;i++){
        if(myUser->type == INSTRUCTOR){
            if(myUser->data.instructor.salary>prevSalary){
                index = i;
                prevSalary = myUser->data.instructor.salary;
                instructorCount ++;
            }
        }
        myUser = myUser->next;
    }
    myUser = list->head;
    for(int i = 0; i<index;i++){
        myUser = myUser->next;
    }
    if(instructorCount == 0){
        *dataOut = NULL;
    }else{
        *dataOut = myUser;
    }
    return SUCCESS;
}


/** is_passing_all_classes
 *
 * Traverses the struct user_list, finding the student with the given name and 
 * determining whether they're passing all their classes.
 * 
 * We say a student is passing a class if their grade is greater than 
 * or equal to 60.
 *
 * You should make sure your code only considers students, even if there is 
 * an instructor of the same name!
 *
 * If a student is not taking any classes, they are NOT considered to be passing.
 *
 * @param list a pointer to the struct user_list structure
 * @param dataOut A pointer to int used to return whether or not the student 
 *                is passing their classes. Insert 1 if they are passing, 
 *                0 if they are not, or -1 if the user_list is NULL or empty 
 *                or does not contain the student with the given name.
 * @return FAILURE if the struct user_list is NULL or empty or does not contain
 *                 the student named, else SUCCESS
 */
int is_passing_all_classes(struct user_list *list, char *name, int *dataOut)
{
    if(!list){
        *dataOut = -1;
        return FAILURE;
    }
    int found = 0;
    *dataOut = 1;
    struct user *myUser =  list->head;
    for(int i = 0; i<list->size;i++){
        if(myUser->type == STUDENT && strcmp(myUser->name,name) == 0){
            found = 1;
            for(int j = 0; j<myUser->data.student.num_classes;j++){
                if(myUser->data.student.grades[j]<60){
                    *dataOut = 0;
                }
            }
            if(myUser->data.student.num_classes==0){
                *dataOut = 0;
            }
        }
        myUser= myUser->next;
    }
    if(found == 0){
        *dataOut = -1;
        return FAILURE;
    }
    return SUCCESS;
}

/** end_semester
 *
 * Traverses the struct user_list, performing an operation on each user.
 *
 * For students:
 *    - All classes should be dropped (num_classes = 0)
 *    - The grades array should be updated accordingly (set to NULL)
 *    - You should not leak memory while doing this
 * For instructors:
 *    - You should add 10000 to their current salary.
 *
 * @param list a pointer to the struct user_list structure
 * @return FAILURE if the struct user_list is NULL or empty,
 *                else SUCCESS
 */
int end_semester(struct user_list *list)
{
    if(!list||list->size==0){
        return FAILURE;
    }
    struct user *myUser =  list->head;
    for(int i = 0; i<list->size;i++){
        if(myUser->type == STUDENT){
            myUser->data.student.num_classes=0;
            free(myUser->data.student.grades);
            myUser->data.student.grades = NULL;
        }else if(myUser->type == INSTRUCTOR){
            myUser->data.instructor.salary = myUser->data.instructor.salary + 10000;
        }
        myUser = myUser->next;
    }
    return SUCCESS;
}