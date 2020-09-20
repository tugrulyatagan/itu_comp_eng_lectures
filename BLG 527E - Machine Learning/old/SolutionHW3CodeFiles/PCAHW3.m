function [ Z , W ] = PCAHW3( X , dim )
%This function analizes principal components of X and returns transform
%Input variables
%X = input data matrix
%dim = desired output dimension

%Output variables
%Z = mapped data
%W = transform function

[m,n]=size(X);

for count=1:n,
    
    X(:,count)=X(:,count)-(sum(X(:,count))/m);
    
end

%Covariance matrix of X
covX=cov(X);

%Find eigenvalues and eigenvectors
[v,d]=eig(covX);
d=max(d).';

%Sort eigenvalues to find maximums and sort vectors with the same indices
[d,ind]=sort(abs(d));
v=v(:,ind);

%Construct transform matrix with eigenvectors corresponding to largest
%eigenvalues
for count=1:dim
    
    W(:,count)=v(:,end-count+1);
       
end

Z=(((W.')*(X.')).');


end

