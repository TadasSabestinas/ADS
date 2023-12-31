#include "big_int.h"
#include <stdio.h>
#include <stdlib.h>


void delete_int(big_int *head) {
    big_int *tmp;

    while (head != NULL) {
        tmp = head;
        head = head->next;
        free(tmp);
    }

}

void remove_zeroes(big_int **head) {
    big_int *current = *head;
    big_int *previous = NULL;
    while (current->number == 0) {
        if (current->next == NULL) {
            break;
        }
        previous = current;
        current = current->next;
        current->previous = NULL;
        previous->next = NULL;
        free(previous);
    }
    *head = current;
}

void memory_Allocation_Check(void *pointer) {
    if (pointer == NULL) {
        printf("Cannot allocate memory\n");
        exit(1);
    }
}

void assign_int(big_int **head, char *number) {
    if (*head != NULL) {
        delete_int(*head);
    }
    *head = NULL;
    long long i = 0;
    big_int *last_node = (big_int *) malloc(sizeof(struct big_int));
    while (number[i] != '\0') {

        char digit = number[i] - 48;

        if (number[i] == '-' && i == 0) {
            ++i;
            if (number[i] < 48 || number[i] > 57) {
                printf("Not valid input\n");
                return;
            }
            digit = 0 - (number[i] - 48);
        } else if (number[i] == '+' && i == 0) {
            ++i;
            if (number[i] < 48 || number[i] > 57) {
                printf("Not valid input\n");
                return;
            }
            digit = number[i] - 48;
        } else if (number[i] < 48 || number[i] > 57) {
            *head = NULL;
            printf("Not valid input\n");
            return;
        }
        big_int *new_node = (big_int *) malloc(sizeof(struct big_int));

        memory_Allocation_Check(new_node);

        new_node->number = digit;
        new_node->next = NULL;

        if (*head == NULL) {
            new_node->previous = NULL;
            *head = new_node;
            last_node = new_node;
        } else {
            last_node->next = new_node;
            new_node->previous = last_node;
            last_node = new_node;
        }

        ++i;
    }
    remove_zeroes(head);
}


big_int *add_int(big_int *a_original, big_int *b_original) {
    big_int *a = NULL;
    copy_int(a_original, &a);

    big_int *b = NULL;
    copy_int(b_original, &b);


    big_int *temp = (big_int *) malloc(sizeof(big_int));
    memory_Allocation_Check(temp);
    char sum;
    int carry = 0;
    int sign = 0;
    if (a->number < 0 && b->number < 0) {
        sign = 1;
        a->number = -1 * a->number;
        b->number = -1 * b->number;
    } else if (a->number > 0 && b->number < 0) {
        b->number = -1 * b->number;
        big_int *c = NULL;
        c = subtract_int(a, b);
        //TEMP
        delete_int(a);
        delete_int(b);
        return c;
    } else if (a->number < 0 && b->number > 0) {
        sign = 1;
        a->number = -1 * a->number;
        big_int *c = NULL;
        c = subtract_int(a, b);
        //TEMP
        delete_int(a);
        delete_int(b);
        return c;
    }

    while (a->next != NULL) {
        a = a->next;
    }
    while (b->next != NULL) {
        b = b->next;
    }


    if (a->number + b->number >= 10) {
        sum = a->number + b->number - 10;
        carry = 1;
    } else {
        sum = a->number + b->number;
        carry = 0;
    }
    temp->next = NULL;
    temp->previous = NULL;
    temp->number = sum;


    while (a->previous != NULL || b->previous != NULL) {
        if (a->previous == NULL) {
            a->number = 0;
        } else a = a->previous;

        if (b->previous == NULL) {
            b->number = 0;
        } else b = b->previous;

        big_int *new_node = (big_int *) malloc(sizeof(big_int));
        memory_Allocation_Check(new_node);
        if (carry == 1) {
            char imaginary_sum = a->number;
            a->number = imaginary_sum + 1;
            carry = 0;
        }
        if (a->number + b->number >= 10) {
            sum = a->number + b->number - 10;
            carry = 1;
        } else {
            sum = a->number + b->number;
            carry = 0;
        }
        new_node->number = sum;
        new_node->next = temp;
        temp->previous = new_node;
        new_node->previous = NULL;
        temp = new_node;
    }
    if (carry == 1) {
        big_int *new_node = (big_int *) malloc(sizeof(big_int));
        memory_Allocation_Check(new_node);
        new_node->number = 1;
        new_node->next = temp;
        temp->previous = new_node;
        new_node->previous = NULL;
        temp = new_node;
    }
    while (temp->number == 0 && temp->next != NULL) {
        big_int *fake = NULL;
        fake = temp;
        fake = fake->next;
        free(temp);
        temp = fake;
    }
    if (sign == 0){
        //TEMP
        delete_int(a);
        delete_int(b);
        return temp;
    }
    else {
        temp->number = -1 * temp->number;
        //TEMP
        delete_int(a);
        delete_int(b);
        return temp;
    }
}

void free_big_int(big_int *a) {
    big_int *current = a;
    while (current != NULL) {
        big_int *next = current->next;
        free(current);
        current = next;
    }
}

big_int *multiply_int(big_int *a, big_int *b) {

    int zero = 0;
    big_int *temp = (big_int *) malloc(sizeof(big_int));
    memory_Allocation_Check(temp);
    big_int *answer = (big_int *) malloc(sizeof(big_int));
    memory_Allocation_Check(answer);
    big_int *fake_answer = (big_int *) malloc(sizeof(big_int));
    fake_answer = NULL;
    char sum = 0;
    int carry = 0;
    int sign = 0;
    if (a->number < 0 && b->number < 0) {
        sign = 0;
        a->number = -1 * a->number;
        b->number = -1 * b->number;
    } else if (a->number > 0 && b->number < 0) {
        sign = 1;
        b->number = -1 * b->number;
    } else if (a->number < 0 && b->number > 0) {
        sign = 1;
        a->number = -1 * a->number;
    }
    //go to the beggining
    while (a->next != NULL) {
        a = a->next;
    }
    while (b->next != NULL) {
        b = b->next;
    }

    //make the first node
    if (a->number * b->number >= 10) {
        char counter = a->number * b->number;
        while (counter >= 10) {
            carry++;
            counter -= 10;
        }
        sum = counter;
    } else {
        sum = a->number * b->number;
        carry = 0;
    }
    temp->next = NULL;
    temp->previous = NULL;
    temp->number = sum;

    //multiply_int algorithm
    sum = 0;

    answer->next = NULL;
    answer->previous = NULL;
    answer->number = 0;

    do {

        if (zero > 0) {
            b = b->previous;
            int fake = zero;

            temp = (big_int *) malloc(sizeof(big_int));
            temp->next = NULL;
            temp->previous = NULL;
            temp->number = 0;

            while (fake > 1) {
                big_int *zero = (big_int *) malloc(sizeof(big_int));
                zero->next = temp;
                zero->previous = NULL;
                temp->previous = zero;
                zero->number = 0;
                temp = zero;
                fake--;
            }

            ///here lies the forbiden code of laziness
            if (a->number * b->number >= 10) {
                int counter = a->number * b->number;
                while (counter >= 10) {
                    carry++;
                    counter -= 10;
                }
                sum = counter;
            } else {
                sum = a->number * b->number;
                carry = 0;
            }
            big_int *new_node = (big_int *) malloc(sizeof(big_int));
            new_node->next = temp;
            new_node->previous = NULL;
            temp->previous = new_node;
            new_node->number = sum;
            temp = new_node;
            sum = 0;
            ///here lies the forbiden code of laziness
        }

        while (a->previous != NULL) {
            a = a->previous;
            big_int *new_node = (big_int *) malloc(sizeof(big_int));
            memory_Allocation_Check(new_node);
            if (carry > 0) {
                sum = carry;
                carry = 0;
            }
            if (a->number * b->number + sum >= 10) {
                int counter = a->number * b->number + sum;
                while (counter >= 10) {
                    carry++;
                    counter -= 10;
                }
                sum = counter;
            } else {
                sum += a->number * b->number;
                carry = 0;
            }
            new_node->number = sum;
            new_node->next = temp;
            temp->previous = new_node;///changes
            new_node->previous = NULL;
            temp = new_node;

            sum = 0;
        }
        if (carry > 0) {
            big_int *new_node = (big_int *) malloc(sizeof(big_int));
            memory_Allocation_Check(new_node);
            new_node->number = carry;
            new_node->next = temp;
            temp->previous = new_node;///changes
            new_node->previous = NULL;
            temp = new_node;
        }

        fake_answer = NULL;
        fake_answer = add_int(temp, answer);
        free_big_int(answer);

        copy_int(fake_answer, &answer);
        //print_int(answer);


        free_big_int(fake_answer);

        while (a->next != NULL) {
            a = a->next;
        }

        free_big_int(temp);
        carry = 0;
        zero++;
    } while (b->previous != NULL);


    if (sign == 0)
        return answer;
    else {
        answer->number = -1 * answer->number;
        return answer;
    }
}


void print_int(big_int *head) {
    big_int *current_node = head;
    if (current_node == NULL) {
        printf("No data given\n");
        return;
    }

    while (current_node != NULL) {
        if (current_node == head && current_node->number < 0) {
            printf("-%c", 0 - (current_node->number) + 48);
        } else {
            printf("%c", (current_node->number) + 48);
        }
        current_node = current_node->next;
    }
    // printf("\n");
//    //print backwards
//    current_node = head;
//    while (current_node->next != NULL){
//        current_node = current_node->next;
//    }
//    while(current_node != NULL){
//        if(current_node == head && current_node->number < 0){
//            printf("-%c", 0 - (current_node->number) + 48);
//        } else {
//            printf("%c", (current_node->number)+48);
//        }
//        current_node = current_node->previous;
//    }
//    printf("\n");
}

void copy_int(big_int *original, big_int **copy) {
    big_int *last_node = (big_int *) malloc(sizeof(big_int));
    memory_Allocation_Check(last_node);
    last_node->number = original->number;
    last_node->next = NULL;
    last_node->previous = NULL;
    *copy = last_node;
    while (original->next != NULL) {
        original = original->next;
        big_int *new_node = (big_int *) malloc(sizeof(struct big_int));
        memory_Allocation_Check(new_node);
        new_node->number = original->number;
        new_node->previous = last_node;
        new_node->next = NULL;
        last_node->next = new_node;
        last_node = new_node;
    }
}

void pure_subtraction(big_int *bigger, big_int *smaller) {

    int carry = 0;
    char bigger_num;
    char smaller_num;
    while (smaller->previous != NULL) {
        bigger_num = bigger->number;
        smaller_num = smaller->number;

        if (carry > 0) {
            --carry;
            if (bigger_num == 0) {
                ++carry;
                bigger_num += 9;
            } else {
                --bigger_num;
            }
        }

        if (smaller_num > bigger_num) {
            ++carry;
            bigger_num += 10;
        }

        bigger->number = bigger_num - smaller_num;
        bigger = bigger->previous;
        smaller = smaller->previous;
    }

    bigger_num = bigger->number;
    smaller_num = smaller->number;

    if (carry > 0) {
        --carry;
        if (bigger_num == 0) {
            ++carry;
            bigger_num += 9;
        } else {
            --bigger_num;
        }
    }
    if (smaller_num > bigger_num) {
        ++carry;
        bigger_num += 10;
    }
    bigger->number = bigger_num - smaller_num;

    while (carry != 0) {
        bigger = bigger->previous;
        --carry;
        if (bigger->number == 0) {
            ++carry;
            bigger->number += 9;
            //bigger = bigger->previous;
        } else {
            --(bigger->number);
        }
    }

    while (bigger->previous != NULL) {
        bigger = bigger->previous;
    }
}

big_int *subtract_int(big_int *first_number, big_int *second_number) {
    big_int *difference = malloc(sizeof(big_int));
    remove_zeroes(&first_number);
    remove_zeroes(&second_number);

    big_int *first_copy = NULL;
    copy_int(first_number, &first_copy);
    big_int *second_copy = NULL;
    copy_int(second_number, &second_copy);

    int type = 1;
    //TYPE: 10 - first is smaller than second
    //TYPE: 100 - second is smaller
    //TYPE: 20 - both minus, first is smaller than second
    //TYPE: 200 - both minus, second is smaller

    if (first_number->number >= 0 && second_number->number < 0) {//10-(-1) or 0 -(-1)
        second_copy->number = 0 - second_copy->number;
        difference = add_int(first_copy, second_copy);
        free(first_copy);
        free(second_copy);
        return difference;
    } else if (first_number->number < 0 && second_number->number > 0) {//-10-1 -> 10 + 1 ->11 -> -11
        first_copy->number = 0 - first_copy->number;//-10->10
        difference = add_int(first_copy, second_copy);
        difference->number = 0 - difference->number;
        free(first_copy);
        free(second_copy);
        return difference;
    } else if (first_number->number < 0 && second_number->number < 0) {//-10-(-1)->-10+1->10-1->9->-9
        first_copy->number = 0 - first_copy->number;//-10->10
        second_copy->number = 0 - second_copy->number;//-1->1
        ++type;//TEMP
        //10 -1 = 9, then turn 9 to -9
    }

    big_int *first_tmp = malloc(sizeof(big_int));
    memory_Allocation_Check(first_tmp);
    first_tmp = first_copy;

    big_int *second_tmp = malloc(sizeof(big_int));
    memory_Allocation_Check(second_tmp);
    second_tmp = second_copy;
    //see if first is smaller than second
    while (first_tmp->next != NULL || second_tmp->next != NULL) {
        if (first_tmp->next == NULL) {
            type *= 10;
            while (second_tmp->next != NULL) {
                second_tmp = second_tmp->next;
            }
            break;
        } else if (second_tmp->next == NULL) {
            type *= 100;
            while (first_tmp->next != NULL) {
                first_tmp = first_tmp->next;
            }
            break;
        }

        first_tmp = first_tmp->next;
        second_tmp = second_tmp->next;
    }

    if (type < 10) {
        if (first_copy->next == NULL && second_copy->next == NULL) {
            if (first_copy->number > second_copy->number) {
                difference->number = first_copy->number - second_copy->number;
                if (type == 2) {
                    difference->number = 0 - difference->number;
                }
                difference->next = NULL;
                difference->previous = NULL;
                return difference;
            } else if (first_copy->number < second_copy->number) {
                difference->number = first_copy->number - second_copy->number;
                if (type == 2) {
                    difference->number = 0 - difference->number;
                }
                difference->next = NULL;
                difference->previous = NULL;
                return difference;
            } else {
                difference->number = 0;
                difference->next = NULL;
                difference->previous = NULL;
                return difference;
            }
        }

        while (first_copy->next != NULL || second_copy->next != NULL) {
            if (first_copy->number > second_copy->number) {
                type *= 100;
                break;
            } else if (first_copy->number < second_copy->number) {
                type *= 10;
                break;
            } else {
                first_copy = first_copy->next;
                second_copy = second_copy->next;
                if (first_copy->next == NULL && second_copy->next == NULL) {
                    if (first_copy->number == second_copy->number) {
                        difference->number = 0;
                        difference->next = NULL;
                        difference->previous = NULL;
                        return difference;
                    } else {
                        if (first_copy->number > second_copy->number) {
                            type *= 100;
                            break;
                        } else {
                            type *= 10;
                            break;
                        }
                    }
                }
            }
        }
    }

    while (first_copy->previous != NULL) {
        first_copy = first_copy->previous;
    }
    while (second_copy->previous != NULL) {
        second_copy = second_copy->previous;
    }

    //printf("%d\n" ,type);
    switch (type) {
        case 10:
            pure_subtraction(second_tmp, first_tmp);
            remove_zeroes(&second_copy);
            second_copy->number = 0 - second_copy->number;
            difference = second_copy;
            delete_int(first_copy);
            return difference;
        case 100:
            pure_subtraction(first_tmp, second_tmp);
            remove_zeroes(&first_copy);
            difference = first_copy;
            delete_int(second_copy);
            return difference;
        case 20:
            pure_subtraction(second_tmp, first_tmp);
            remove_zeroes(&second_copy);
            difference = second_copy;
            delete_int(first_copy);
            return difference;
        case 200:
            pure_subtraction(first_tmp, second_tmp);
            remove_zeroes(&first_copy);
            difference = first_copy;
            difference->number = 0 - first_copy->number;
            delete_int(second_copy);
            return difference;
        default:
            return difference;
    }
}

int check_if_bigger(big_int *first, big_int *second) {
    while (first->previous != NULL) {
        first = first->previous;
    }
    while (second->previous != NULL) {
        second = second->previous;
    }
    remove_zeroes(&first);
    remove_zeroes(&second);

    //check by length
    while (first->next != NULL) {
        if (second->next == NULL) {
            return 1;
        }
        first = first->next;
        second = second->next;
    }
    if (second->next != NULL) {
        return 0;
    }

    //rewind list
    while (first->previous != NULL) {
        first = first->previous;
    }
    while (second->previous != NULL) {
        second = second->previous;
    }

    //check by value
    while (second->next != NULL) {
        if (first->number < second->number) {
            return 0;
        } else if (first->number > second->number) {
            return 1;
        }
        first = first->next;
        second = second->next;
    }

    if (first->number > second->number) {
        return 1;
    } else {
        return 0;
    }

}

void append(struct big_int **head_value, char new_data) {
    big_int *new_item = (big_int *) malloc(sizeof(big_int));
    memory_Allocation_Check(new_item);
    big_int *last = *head_value;

    new_item->number = new_data;
    new_item->next = NULL;

    if (*head_value == NULL) {
        new_item->previous = NULL;
        *head_value = new_item;
        return;
    }
    while (last->next != NULL) {
        last = last->next;
    }

    last->next = new_item;
    new_item->previous = last;
}

int check_if_equal(big_int *first, big_int *second) {
    while (first->previous != NULL) {
        first = first->previous;
    }
    while (second->previous != NULL) {
        second = second->previous;
    }
    remove_zeroes(&first);
    remove_zeroes(&second);

    //check by length
    while (first->next != NULL) {
        if (second->next == NULL) {
            return 0;
        }
        first = first->next;
        second = second->next;
    }
    if (second->next != NULL) {
        return 0;
    }

    //rewind list
    while (first->previous != NULL) {
        first = first->previous;
    }
    while (second->previous != NULL) {
        second = second->previous;
    }

    //check by value
    while (second->next != NULL) {
        if (first->number != second->number) {
            return 0;
        }
        first = first->next;
        second = second->next;
    }

    if (first->number != second->number) {
        return 0;
    } else {
        return 1;
    }
}


big_int *divide_int(big_int *dividend, big_int *divisor) {
    big_int *current_quotient = NULL;
    big_int *save_position = NULL;

    big_int *dividend_copy = NULL;
    copy_int(dividend, &dividend_copy);
    big_int *divisor_copy = NULL;
    copy_int(divisor, &divisor_copy);

    remove_zeroes(&dividend_copy);
    remove_zeroes(&divisor_copy);

    int sign = 0;
    if (divisor_copy->number < 0) {
        divisor_copy->number = 0 - divisor_copy->number;
        ++sign;
    }

    if (dividend_copy->number < 0) {
        dividend_copy->number = 0 - dividend_copy->number;
        ++sign;
    }

    if (dividend_copy->number == 0) {
        append(&current_quotient, 0);
        delete_int(dividend_copy);
        delete_int(divisor_copy);
        return current_quotient;
    } else if (divisor_copy->number == 0) {
        fprintf(stderr, "Division by zero!\n");
        delete_int(dividend_copy);
        delete_int(divisor_copy);
        append(&current_quotient, 0);
        return current_quotient;
    }
    int division = 1;//to track if we still need to divide

    int first_iteration = 1;


    while (division) {
        //make sure we start from number start
        while (divisor_copy->previous != NULL) {
            divisor_copy = divisor_copy->previous;
        }

        if (dividend_copy == NULL) {
            break;
        }
        int too_small = 0;
        if (first_iteration) {
            //set number for first time iteration
            save_position = dividend_copy->next;
            dividend_copy->next = NULL;

            while (check_if_bigger(dividend_copy, divisor_copy) != 1 &&
                   check_if_equal(dividend_copy, divisor_copy) != 1) {
                //move by one
                if (save_position == NULL) {
                    too_small = 1;
                    break;
                }
                dividend_copy->next = save_position;
                dividend_copy = dividend_copy->next;
                save_position = dividend_copy->next;
                dividend_copy->next = NULL;

            }

            if (too_small) {
                append(&current_quotient, 0);
                break;
            }
            first_iteration = 0;
        } else {
            dividend_copy = dividend_copy->next;

            save_position = dividend_copy->next;
            dividend_copy->next = NULL;

            while (check_if_bigger(dividend_copy, divisor_copy) != 1 &&
                   check_if_equal(dividend_copy, divisor_copy) != 1) {
                append(&current_quotient, 0);
                //move by one
                if (save_position == NULL) {
                    too_small = 1;
                    break;
                }
                dividend_copy->next = save_position;
                dividend_copy = dividend_copy->next;
                save_position = dividend_copy->next;
                dividend_copy->next = NULL;
            }

            if (too_small) {
                break;
            }
        }
        //check which is bigger, find end position
        int bigger = 1;
        char count = 0;
        //subtract till smaller
        while (bigger) {
            //rewind
            while (dividend_copy->previous != NULL) {
                dividend_copy = dividend_copy->previous;
            }
            while (divisor_copy->previous != NULL) {
                divisor_copy = divisor_copy->previous;
            }
            dividend_copy = subtract_int(dividend_copy, divisor_copy);
            ++count;

            if (check_if_bigger(dividend_copy, divisor_copy) || check_if_equal(dividend_copy, divisor_copy)) {
                bigger = 1;
            } else {
                bigger = 0;
            }
        }

        append(&current_quotient, count);

        while (dividend_copy->next != NULL) {
            dividend_copy = dividend_copy->next;
        }

        if (save_position == NULL) {
            break;
        }

        dividend_copy->next = save_position;
        save_position->previous = dividend_copy;

    }
    while (current_quotient->previous != NULL) {
        current_quotient = current_quotient->previous;
    }
    if (sign == 1) {
        current_quotient->number = 0 - current_quotient->number;
    }

    delete_int(dividend_copy);
    delete_int(divisor_copy);
    return current_quotient;
}