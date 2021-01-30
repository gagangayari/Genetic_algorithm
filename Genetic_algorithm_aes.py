#!/usr/bin/env python
# coding: utf-8

# In[1]:


import subprocess as sb
from subprocess import PIPE
import numpy as np
import pandas as pd
from sklearn.model_selection import train_test_split
import matplotlib.pyplot as plt

#%% Declare constants
key_len=167
possible_val=['0','1']
populations=100
max_itr=100
max_offsprings=100
p_cross= 0.6
p_mut =0.001
error_vals=[]

#%% Read data file

##Actual output data .
output_data=pd.read_csv('actual_output.csv',header=None)




# In[19]: A chromosome class



class sample:
    def __init__(self):
        self.key=np.random.randint(0,2,key_len)
        self.fitness= -1

#%% In[ ]: generate output from obfuscated code.


def get_output(key):
    """
    Runs a C code by passing the "key" as parameters and creates
    a output csv file based on the given key. 

    Parameters
    ----------
    key : Binary string

    Returns
    -------
    None.

    """
    exe="locked"
    filename="adpcm.c"
    
    temp= [str(k) for k in key]

    run=".\locked"
    aout=[run]
    
    aout.extend(temp)
    # print(aout)
    sb.run(["gcc","-o",exe,filename],shell=True,stdout=PIPE)
    sb.run(aout,shell=True,stdout=PIPE)
    

       
#%% Mutation
    
                
                
def mutation(sample):
    mutation_prob=np.random.uniform(0,1,key_len)<=p_mut
    mutation_index= np.array(np.where(mutation_prob)).ravel()
    
 

    for index in mutation_index:

        if(sample.key[index]==0):
            # print("here","0")
            sample.key[index]=1
        else:
            sample.key[index]=0
    # print(sample.key)
    return sample
            
#%% Crossover
    
def crossover(p1,p2,type="one_point",no_of_offsprings=10):
    
    child1=sample()
    child2=sample()
    if(np.random.uniform()<p_cross):
        if(type=="one_point"):  ##if single split
            split_point=np.random.randint(0,key_len,1)[0]

            child1.key=np.hstack((p1.key[:split_point],p2.key[split_point:]))
            child2.key=np.hstack((p2.key[:split_point],p1.key[split_point:]))

        elif(type=="two_point"):
            split_1=np.random.randint(0,key_len,1)[0]
            split_2=np.random.randint(0,key_len,1)[0]
            while(split_2==split_1):
                split_2=np.random.randint(0,key_len,1)[0]
            
            child1.key=np.hstack((p1.key[:split_1],p2.key[split_1:split_2],p1.key[split_2:]))
            child2.key=np.hstack((p2.key[:split_1],p1.key[split_1:split_2],p2.key[split_2:]))

        elif(type=="uniform"):
            coin=np.random.choice([0,1],1)
            ## flip genes if coin is 1
            # for gene in range(key_len):
            #     if(coin==1):
                    

                
                 

    return (child1,child2)


#%% selection
def selection(samples):
    
    fit_samples=[]
    
    
    for sample in samples:
        if(sample.fitness>=fitness_criteria):
            fit_samples.append(sample)
            
    return fit_samples
    
        
#%% fitness

def fitness(samples):
    
    output=[]
    fit_values=[]
    flag=0
    err=0
    for i,sample in enumerate(samples):
        print(sample.key)
        get_output(sample.key)
        ##output csv is generated with the name cur_output.csv
        output=pd.read_csv("cur_output.csv",header=None)  #predicted output
        ##Scaling down the error by 100
        rss =[np.linalg.norm(np.sqrt(np.mean((output_data-output)**2,axis=1)))/100]
        err+=rss[0]
        print("rss",rss[0])
        if(rss[0]==0):
            print("Exact key found ",sample.key)
            flag=1
            break
        # try:
        fitness_strength=1/rss[0]
        
        sample.fitness=fitness_strength
        fit_values.append(fitness_strength)
        
    error_vals.append(err/100)
    ax=plt.plot(error_vals)
    plt.show()
    
    if(flag):
        index=[i for _ in range(len(samples))]
        return index
    ##sort the fit_values
    fit_values=-1*np.array(fit_values).ravel()
    sorted_index=np.argsort(fit_values)

    return sorted_index  



#%% SGA..
    
visited={}
fig=plt.figure()
xx=0
ax=fig.add_subplot() 
error_vals=[]
best_offspring=sample()
   
    
def sga():
    population=np.array([sample() for _ in range(100)])

    best_offspring=population[0]
    ##select the n fittest samples
    # print("pop",population)
    for _ in range( 1000):
        print(" Iteration :",_)
        indexes=fitness(population)
        population=population[indexes]  ##reordering in order of decreasing fitness score
        # print("pop",population)
        if(len(set(indexes))==1):
            print("Best key found ! ",population[0].key)
            break 

        if(best_offspring.fitness<population[0].fitness):
            best_offspring=population[0]
            print("current best fitness ",best_offspring.fitness)
            print("key : ",best_offspring.key)


        offsprings=[]


        ##selecting two chromosmes with highest fitness
        while(len(offsprings)<=max_offsprings+95): ## generate N offsprings


            ## Perform crossover  
            p1=population[0]  ## selecting fittest chromosomes as parents
            p2=population[1]
            visited[p1.key.tostring()]=1
            visited[p2.key.tostring()]=1
  
            c1,c2=crossover(p1,p2,'two_point')
            while(c1.key.tostring() in visited and c2.key.tostring() in visited):
                c1,c2=crossover(p1,p2)

        
            ##Perform mutation
            c1=mutation(c1)
            c2=mutation(c2)
            while(c1.key.tostring() in visited and c2.key.tostring() in visited):
                c1=mutation(c1)
                c2=mutation(c2)



            offsprings.append(c1)
            offsprings.append(c2)
    

        population = np.array(offsprings)
        
        
    return best_offspring

print(sga())
    







