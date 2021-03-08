#include<bits/stdc++.h>

#define key_size 167
#define mut_prob 0.01
#define xover_prob 0.3


/* Generate random key of size as key_size */
void get_random_bit(struct chrom *c){
    for(int i=0;i<key_size;i++){
        c->key[i]=(random()>RAND_MAX/2);

    }

}



struct chrom
{
    int key[key_size];
    
    //set random key
    for(int i=0;i<key_size;i++){
        key[i]= (random()>RAND_MAX/2);

    }
    
    int fitness= -1;
};



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
void mutation(chrom sample){
    //Mutation in Constants
    //const1 k1-k32
    flip_bits(sample,0,31);
    flip_bits(sample,32,63);
    flip_bits(sample,64,95)
    flip_bits(sample,96,127);
    flip_bits(sample,128,159);

    //Mutation for remaining bits



}

void helper_xover_consts(chrom *mate1,chrom *mate2,int i ,int j){
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

}
void crossover(chrom *mate1,chrom *mate2){
    /* Method for one-point crossover

    */

    //For constants
    helper_xover_consts(mate1,mate2,0,31);
    helper_xover_consts(mate1,mate2,32,63);
    helper_xover_consts(mate1,mate2,64,95);
    helper_xover_consts(mate1,mate2,96,127);
    helper_xover_consts(mate1,mate2,128,159);


    //For remaining bits

    int random_point=random()%7;
    int temp;
    for(int i=point;i<key_size;i++){
        temp=mate2->key[i];
        mate2->key[i]=mate1->key[i];
        mate1->key[i]=temp;

    }
    

/*Selection of Parents*/

//We select 10 random samples and pick the two fittest samples

bool check_if_not_picked(int picked_arr[],int index){


}

int pick_best(struct chrom samples[],int n){

}
void selection (struct chrom samples[],int n){//n is the size of the samples array
    int n_sample=10;
    int first_set[n_sample],second_set[n_sample];
    int count=0,i=0,index;
    //generate  10 random indexes
    while (count!=10 ){
       index= random()/n;
       if( check_if_not_picked(first_set,index) ){
           first_set[i]=index;
       
       }
       count++;
       i++;

    }
    

    

}


/* Calculates the fitness value for each samples*/

void fitness(struct chrom samples[],int n){
    for(int i=0;i<n;i++){


    }


}


    

}

int main(){

}
