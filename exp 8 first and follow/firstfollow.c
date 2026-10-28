#include<stdio.h>
#include<string.h>
#include<ctype.h>

char lhs[20][10], rhs[20][10][10];
int rhs_len[20], n=0;
char nts[20][10]; // non-terminal symbols
int nt_cnt=0;
char follow_sets[20][20][10];
int follow_cnt[20] = {0};


//helper to insert unique element into a set
void add_set(char set[][10], int *cnt, const char *val){ 
    for(int i=0; i< *cnt;i++){
        if (strcmp(set[i], val)==0) return;
    }
    strcpy(set[(*cnt)++], val);
}
int is_nt(const char *s){ return isupper(s[0]); } // check if a symbol is a non-terminal

//for computing FIRST set
void get_first(const char *sym, char first_set[][10], int *fc){
    if(!is_nt(sym)){add_set(first_set,fc,sym); return;} // if terminal, add to first set

    for(int i=0; i<n; i++){
        if(strcmp(lhs[i],sym)!=0) continue; // find productions for the non-terminal
        int eps=1; // flag to check if epsilon can be derived
        for(int j=0; j<rhs_len[i] && eps; j++){ // iterate through symbols in the production
            char sub[20][10]; int sc=0;
            eps=0;
            get_first(rhs[i][j], sub, &sc); // get first of the production
            for(int k=0; k<sc; k++){
                if(strcmp(sub[k], "#")==0) eps=1; // if epsilon is in first, continue to next symbol
                else add_set(first_set, fc, sub[k]); // add to first set
            }
        }
        if (eps) add_set(first_set, fc, "#"); // if all symbols can derive epsilon, add epsilon to first set
    }
}
    

//for computing FOLLOW set

int find_nt(const char *sym) {
    for (int i = 0; i < nt_cnt; i++) {
        if (strcmp(nts[i], sym) == 0)
            return i;
    }
    return -1;
}

void compute_follow() {
    // Initialize FOLLOW(start symbol) with $
    int start = find_nt(lhs[0]);
    if (start != -1)
        add_set(follow_sets[start], &follow_cnt[start], "$");

    int changed;

    do {
        changed = 0;

        for (int i = 0; i < n; i++) {
            int A = find_nt(lhs[i]);
            if (A == -1) continue;

            for (int j = 0; j < rhs_len[i]; j++) {
                int B = find_nt(rhs[i][j]);

                // FOLLOW applies only to non-terminals
                if (B == -1) continue;

                int old_count = follow_cnt[B];
                int nullable = 1;

                // FIRST of the symbols after B
                for (int k = j + 1;
                     k < rhs_len[i] && nullable; k++) {

                    char sub[20][10];
                    int sc = 0;

                    get_first(rhs[i][k], sub, &sc);
                    nullable = 0;

                    for (int x = 0; x < sc; x++) {
                        if (strcmp(sub[x], "#") == 0) {
                            nullable = 1;
                        } else {
                            add_set(follow_sets[B],
                                    &follow_cnt[B], sub[x]);
                        }
                    }
                }
                // If B is at the end, or everything after B
                // can derive epsilon, add FOLLOW(A) to FOLLOW(B).
                if (nullable) {
                    for (int x = 0; x < follow_cnt[A]; x++) {
                        add_set(follow_sets[B],
                                &follow_cnt[B],
                                follow_sets[A][x]);
                    }
                }

                if (follow_cnt[B] > old_count)
                    changed = 1;
            }
        }

    } while (changed);
}


int main(){
    printf("Enter number of productions : ");
    scanf("%d",&n);
    printf("Enter productions in the form A -> aB (use # for epsilon):\n");

    for(int i=0; i<n; i++){
        char buf[100];
        scanf("%s -> %s", lhs[i], buf);

        //register unique non-terminals
        int found=0;
        for(int j=0; j<nt_cnt; j++){
            if(strcmp(nts[j], lhs[i])==0) found=1; // check if non-terminal is already in the list
        }
        if(!found) strcpy(nts[nt_cnt++], lhs[i]); // add to non-terminal list if not already present

        //tokenize the rhs into individual symbols
        int len= strlen(buf), pos=0;
        rhs_len[i]=0;
        while(pos<len){
                if (strncmp(&buf[pos], "id", 2)==0){ // check for 'id' terminal
                    strcpy(rhs[i][rhs_len[i]++], "id"); // handle 'id' as a special case
                    pos+=2;
                }
            else if(strncmp(&buf[pos], "if",2)==0){
                strcpy(rhs[i][rhs_len[i]++],"if");
                pos+=2;
            }
            else if(strncmp(&buf[pos],"then",4)==0){
                strcpy(rhs[i][rhs_len[i]++],"then");
                pos+=4;
            }
            else if(strncmp(&buf[pos],"else",4)==0){
                strcpy(rhs[i][rhs_len[i]++],"else");
                pos+=4;
            }
            else if (isupper(buf[pos])){
                char tok[10]={buf[pos++], '\0'}; // handle non-terminal symbols
                if (pos < len && buf[pos] =='\'') tok[1] = buf[pos++], tok[2] = '\0';
                strcpy(rhs[i][rhs_len[i]++],tok);
            }
            else{
                char tok[10]={buf[pos++], '\0'}; // handle terminal symbols
                strcpy(rhs[i][rhs_len[i]++],tok); // add terminal to rhs
            }
        }
    }
    printf("\nFirst Sets:\n");
    for (int i=0; i<nt_cnt; i++){
        char f[20][10]; int fc=0; // temporary set for first of the non-terminal
        get_first(nts[i], f, &fc);
        printf("FIRST(%s) = { ", nts[i]);
        for(int k=0; k<fc; k++){
            printf("%s ", f[k]);
        }
        printf("}\n");
    }
    
printf("\nFollow Sets:\n");

compute_follow();

for (int i = 0; i < nt_cnt; i++) {
    printf("FOLLOW(%s) = { ", nts[i]);

    for (int k = 0; k < follow_cnt[i]; k++) {
        printf("%s ", follow_sets[i][k]);
    }

    printf("}\n");
}

    return 0;
}




/*
sample output


E -> TE'
E' -> +TE'
E' -> #
T -> FT'
T' -> *FT'
T' -> #
F -> (E)
F -> id


expected output


FIRST Sets:
FIRST(E) = { ( id }
FIRST(E') = { + # }

FIRST(T) = { ( id }
FIRST(T') = { * # }
FIRST(F) = { ( id }

FOLLOW Sets:
FOLLOW(E) = { $ ) }
FOLLOW(E') = { $ ) }
FOLLOW(T) = { + $ ) }
FOLLOW(T') = { + $ ) }
FOLLOW(F) = { * + $ ) }


*/

/*
second input



S -> ifEthenSS'
S' -> elseS 
S' -> #
E -> id 
*/

