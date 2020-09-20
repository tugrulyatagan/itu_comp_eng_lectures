function [ mean,eps,pi ] = EM( X ,dim , max_iter , initmean )

mulvargauss= @(x,mean,eps) (1/sqrt((2*3.14*norm(eps))))*exp(-((x.'-mean).'*inv(eps)*(x.'-mean)));

%Input variables
%X        := Nx2 data matrix
%dim      := number of clusters 
%max_iter := maximum iterations
%initmean := 2xdim matrix contains [x;y] values for initial mean

%Output variables
%pi   := probs of each cluster
%mean := means of clusters
%eps  := covariance matrices

%Initialization
%Mean initialization
for count=1:dim,
    
    mean{count}=initmean(:,count);

end
%Random initialization
pi=abs(randn(1,dim));
pi=pi/(sum(pi(:)));

for k=1:dim,

    eps{k}=[1 0; 0 1];

end

%Iteration
wb = waitbar(0,'Processing EM-Algorithm');

for iter=1:max_iter,
    waitbar(iter / max_iter)
        
    %Expectation-Step
    for i=1:size(X,1),
        dum=0;
        for k=1:dim,
        
            dum=dum+pi(k)*mulvargauss(X(i,:),mean{k},eps{k});
            
        end
        
        for k=1:dim,
            
            %gamma_ki value (random gaussian)
            gamki(i,k)=pi(k)*mulvargauss(X(i,:),mean{k},eps{k})/dum;       
        
        end
    end
    clear dum;
    
    %Maximization-Step
    for k=1:dim,
        
        %update mean
        dum1=sum(gamki(:,k).*X(:,1))/sum(gamki(:,k));
        dum2=sum(gamki(:,k).*X(:,2))/sum(gamki(:,k));
        meannew{k}=[dum1 ; dum2];
        %clear dummy variable for other purposes
        clear dum1 dum2;
        
        %update probabilities of clusters
        pi(k)=sum(gamki(:,k))/size(X,1);
        
        %update covariances
        dummean=mean{k};
        summ=zeros(2,2);
        
        %summ=0;
        for i=1:size(X,1),
        
            summ=summ+gamki(i,k)*([X(i,1)-dummean(1);X(i,2)-dummean(2)]*[X(i,1)-dummean(1);X(i,2)-dummean(2)].');
        
        end
        
        clear dum1 dum2 dum3 dummean;
        dumeps=summ/sum(gamki(:,k));
        eps{k}=gmmb_covfixer(dumeps); 
        mean{k}=meannew{k};
        
        clear summ;
        
    end
end
close(wb);

end

