%Machine Learning Homework2 Demo
%Aziz Kocanaogullari 504141303
close all;
clear all; 

%Initialize data
Dat=textread('optdigits01.txt');

%%
%Number of features
d=size(Dat,2);

%Prob. of each class
%Since the last column of the feature set determines whether the data
%belongs to set 1 or 2 then we can use '0' as C_0 '1' as C_1 
%Also number of '1's correspond to number of C_1s overall
PC{1}=sum(Dat(:,65))/size(Dat,1);
PC{2}=1-PC{1};

%Detect improper features
%Since entire data matrix has >0 values one can use the summation of each
%column. If the sum. =0 that shows entire column is 0.
sumDat=sum(Dat,1);
%Indices of improper features
impind=find(sumDat<=0);

%Reconstruct the data matrix with proper values
DatRe=Dat;
DatRe(:,impind)=[];

%Number of usable features
d=size(DatRe,2);

%%
%This part is not required since the operation is done by cross validation
%but not randomly selected validation sets.
%Division of reconstructed data into validation and training sets
%Generate random numbers for randomly chosen observations
%ranob=randi([1,360],1,10);
%DatVa=DatRe(ranob,:); %Validation set
%DatTra=DatRe; %Training set
%DatTra(ranob,:)=[];

%%
for x=1:10,

%Division of reconstructed data into validation and training sets
DatVa=DatRe((x-1)*36+1:x*36,:); %Validation set
DatTra=DatRe; %Training set
DatTra((x-1)*36+1:x*36,:)=[];

%Calculation of pij s
%Num of features
for j=1:d-1,
    %Num of data vals.
    for k=1:17
        % 1 corresponds to class 0 / 2 corresponds to class 1
        p{2}(j,k)=sum((DatTra(:,j)==k-1).*DatTra(:,end))/sum(DatTra(:,end));
        p{1}(j,k)=sum((DatTra(:,j)==k-1).*(DatTra(:,end)==0))/(size(DatTra,1)-sum(DatTra(:,end)));
            
    end
end

%The aim is to discriminate class 0 from 1 in other words g_0-g_1>0
%g_0-g_1=sum(zjk+log(p0jk)-log(p1jk))+log(PC0)-log(PC1)
for n=1:size(DatVa,1)
    dis=0;
    for j=1:d-1   
        %Exponential functions are used to avoid log(0)
        dis=log(p{1}(j,DatVa(n,j)+1)+10^-8)-log(p{2}(j,DatVa(n,j)+1)+10^-8)+dis;
        
    end
    dis=dis+log(PC{1}/PC{2});
    label{1}(n)=abs((dis>0)-1);    
    
end

%%
%Calculation with same probabilities
%Since all numbers' probs. are free of feature, one can calculate the
%values of probabilities by ignoring the feature number and taking the mean
%of total appearance of the number.
pp{1}=sum(p{1},1);
pp{2}=sum(p{2},1);
pp{1}=pp{1}/sum(pp{1});
pp{2}=pp{2}/sum(pp{2});

for n=1:size(DatVa,1)
    dis=0;
    for j=1:d-1,
      
        dis=log(pp{1}(DatVa(n,j)+1)+10^-8)-log(pp{2}(DatVa(n,j)+1)+10^-8)+dis;
        
    end    
    
    dis=dis+log(PC{1}/PC{2});
    label{2}(n)=abs((dis>0)-1); 
    
end

%Variables to check correct label rate
label1(x,:)=label{1};
label2(x,:)=label{2};
actuallabels(x,:)=DatRe((x-1)*36+1:x*36 ,end).';

end

%%
%Determining better model

%Confusion matrices
Con1=[sum(sum((label1==1).*(actuallabels==1))) sum(sum((label1==0).*(actuallabels==1)));
    sum(sum((label1==1).*(actuallabels==0))) sum(sum((label1==0).*(actuallabels==0)))];

Con2=[sum(sum((label2==1).*(actuallabels==1))) sum(sum((label2==0).*(actuallabels==1)));
    sum(sum((label2==1).*(actuallabels==0))) sum(sum((label2==0).*(actuallabels==0)))];

%Calculating error rates
%Calculating t-distribution vales
p1=sum(abs(label1-actuallabels),1)/size(label1,1);
p2=sum(abs(label2-actuallabels),1)/size(label2,1);
pi=p1-p2;

m=sum(pi)/size(label2,2);

var=sum((pi-m).^2)/(size(label2,2)-1);

%Hypothesis testing via t distribution since we have calculated the
%variance value from the samples

%If the condition satisfies the %95 confidence interval that shows
%algorithm 1 yields better results than the second algorithm

z=sqrt(size(label2,2))*m/sqrt(var);

%%
%Display Results
%Probabilities of the classes (supervised)
PC{1}
PC{2}

%Confusion matrices
Con1
Con2

%Hypothesis testing
disp(strcat('Calculated t value:',num2str(abs(z))));

