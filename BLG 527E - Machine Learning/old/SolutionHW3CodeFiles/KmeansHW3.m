function [ b , mean , error] = KmeansHW3( X , dim  )
%This function clusters given data set using the k-means algorithm
%Ýnput Variables
%X         := input data matrix
%dim       := number of clusters to be obtained

%Output variables
%b     := calculated labels
%mean  := means of clusters
%error := reconstruction error

[m,n]=size(X);


%Initialize means
%Convergence is independent of starting point so picking up starting
%condition randomly wrt. Forgy-Pertition is suitable
for count=1:dim,
   
    %Forgy Pertition
    mean(count,:)=X(randint(1,1,[1,m]),:);
    
end

%Algorithm
criterion=1;
bold=ones(m,dim);
b=zeros(m,dim);

while criterion>0
    b=zeros(m,dim);
    %Calculate labels
    for i=1:m,  
        
        %Calculate label vectors
        for count=1:dim,
                       
            dum(count)=sum((X(i,:)-mean(count,:)).^2);
            
        end 
             
        ind=find(dum==min(dum));
        
        b(i,ind)=1;
        
    end
    
    %Update means    
    for count=1:dim,
        
        dumx=sum(b(:,count).*X(:,1))/sum(b(:,count));
        dumy=sum(b(:,count).*X(:,2))/sum(b(:,count));
        mean(count,1)=dumx;
        mean(count,2)=dumy;
        
    end    
    
    
    %Compute criterion      
    criterion=sum(sum(((bold-b).^2)));
    bold=b;
    
end

%Calculate reconstruction error
error=0;
for count=1:dim,
    for i=1:m,
   
        error=error+b(i,count)*sum((X(i,:)-mean(count,:)).^2);
    
    end
end

end

