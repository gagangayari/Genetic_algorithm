#include<stdlib.h>
#include<stdio.h>
#include<string.h>



#define key_size 167
#define mut_prob 0.01
#define xover_prob 0.3


/* Display */

void display( int a[],int n){
    printf("\n");
    for(int i=0;i<n;i++){
        printf("%d ",a[i]);
    }
    printf("\n");
}





/* ############# Structures #############*/


struct chrom
{
    int key[key_size];
    
    //set random key
    for(int i=0;i<key_size;i++){
        key[i]= (random()>RAND_MAX/2);

    }
    
    int fitness= -1;
};

struct custom_struct{
    int first,second;
};




/*  ################## MUTATION ############# */

/*Flip bits at some location*/
void flip_bits(sample,int i,int j){
    //Exploitation
    for(int k=16;k<32;k++){
        if(random()/RAND_MAX < mut_prob){
            if(sample[i+k]==0){
                sample[i+k]=1;
            }
            else{
                sample[i+k]=0;
            }

        }
        


    }


}
void mutation(struct chrom sample){
    //Mutation in Constants
    //const1 k1-k32
    flip_bits(sample,0,31);
    flip_bits(sample,32,63);
    flip_bits(sample,64,95)
    flip_bits(sample,96,127);
    flip_bits(sample,128,159);

    //Mutation for remaining bits



}
/* ################ CROSSOVER ################## */
/* Crossover only for constants*/
void helper_xover_consts(struct chrom *mate1,struct chrom *mate2,int i ,int j){
    /*i and j are the starting and ending indexes of the constants
    E.g For constant 1: i=0,j=31
    */
    int point=random() % 32;
    int temp;
    for(int k=point;k<=j;k++){
        temp=mate2->key[k];
        mate2->key[k]=mate2->key[k];
        mate1->key[k]=temp;
    }



/* Method for one-point crossover*/
void crossover(struct chrom *mate1,struct chrom *mate2) {
    
    //For constants
    helper_xover_consts(mate1,mate2,0,31);
    helper_xover_consts(mate1,mate2,32,63);
    helper_xover_consts(mate1,mate2,64,95);
    helper_xover_consts(mate1,mate2,96,127);
    helper_xover_consts(mate1,mate2,128,159);


    //For remaining bits

    int random_point=random()%7;
    int temp;
    for(int i=random_point;i<key_size;i++){
        temp=mate2->key[i];
        mate2->key[i]=mate1->key[i];
        mate1->key[i]=temp;

    }
}

    

/* ##################### Selection of Parents ##########################*/

//We select 10 random samples and pick the two fittest samples

int check_if_not_picked(int picked_arr[],int index,int n){
    for(int i=0;i<n;i++){
        if(picked_arr[i]==index){
            return 0;
        }
    }
    return 1;

}

/* Choose the fittest sample from an array of samples8*/
int pick_best(struct chrom samples[],int arr[],int n){
    struct chrom fittest_sample=samples[0];
    int index=0;
    for(int i=0;i<n;i++){
        if(fittest_sample->fitness < samples[i]->fitness){
            fittest_sample=sample[i];
        }

    }
    
    return index;

}


/* Initialise all elements of an array to -1 */
void initializer(int arr[],int n){
    for(int i=0;i<n;i++){
        arr[i]=-1;
    }

}
/* Parent selection */

struct chrom selection (struct chrom samples[],int n){//n is the size of the samples array
    int n_sample=10;
    int first_set[n_sample],second_set[n_sample];
    
    //Initialise array values to -1
    initializer(first_set,n_sample);
    initializer(second_set,n_sample);


    int count1=0,count2=0,i=0,j=0,index;
    //generate  10 random indexes
    while (count!=10 ){
       index= random()/n;
       if( check_if_not_picked(first_set,index,n_sample) ){
           first_set[i]=index;
           count++;
           i++;   
       }

    }
    int parent1=pick_best(samples,first_set,n_sample);
    
    while (count2!=10 ){
       index= random()/n;
       if( check_if_not_picked(second_set,index,n_sample) ){
           second_set[i]=index;
           count2++;
           j++;   
       }

    }

    int parent2=pick_best(samples,second_set,n_sample);

    struct custom_struct parents;
    parents.first=parent1;
    parents.second=parent2;

    return parents;
    

}



/* Calculates the fitness value for each samples*/

void fitness(struct chrom samples[],int n){
    for(int i=0;i<n;i++){
        continue;

    }


}








}

int main(){

    struct chrom a,b;
    display(a->key,key_size);
    return 0;

}

