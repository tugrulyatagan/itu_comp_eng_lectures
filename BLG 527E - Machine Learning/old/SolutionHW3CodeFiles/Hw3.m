%Machine Learning HW3 Demo
%StudentName-StudentID

close all;
clear all;

X=dlmread('optdigits01.txt');

[m,n]=size(X);

sumX=sum(X,1);
%Indices of improper features
impind=find(sumX<=0);

%Reconstruct the data matrix with proper values
DatRe=X;
DatRe(:,impind)=[];
XRe=DatRe(:,1:end-1);

%%
%Question-1
%PCA on entire dataset
%Calculate PCA except the last feature ('class label')
[Map1,w{1}]=PCAHW3(XRe,2);

figure();
plot(Map1(1:178,2),Map1(1:178,1),'*b');
hold();
plot(Map1(179:end,2),Map1(179:end,1),'or');
title('PCA on Class0 and Class1 together');
legend('class-0','class-1');

%Knn5-model
mdl = fitcknn(Map1,X(:,end),'NumNeighbors',5);

label=predict(mdl,Map1);
disp(strcat('Error for PCA on all:',num2str(abs(sum(label-X(:,65))))));

%PCA on class1 and class0 divided
%Calculate two PCAs seperetely. This is not feasible where the two
%transformations are different. So their mappings are different.
[PCAX1,w{1}]=PCAHW3(XRe(1:178,:),2);
[PCAX2,w{2}]=PCAHW3(XRe(179:end,:),2);

figure();
plot(PCAX1(:,2),PCAX1(:,1),'*b');
hold();
plot(PCAX2(:,2),PCAX2(:,1),'or');
title('PCA on Class0 and Class1 seperately');
legend('class-0','class-1');

mdl = fitcknn([PCAX1;PCAX2],X(:,end),'NumNeighbors',5);
label=predict(mdl,[PCAX1;PCAX2]);
disp(strcat('Error for PCA seperately:',num2str(abs(sum(label-X(:,65))))));

%%
%Question-2
%Usage of mRMR-MID to choose most efficient features
%first input := candidete feature matrix
%second input := class labels for given features (should be a vector)
%third input := Number of features to be picked off
%output := most feasible k features to be used

rec{1}=mrmr_mid_d(XRe,X(:,65),2),
ind=rec{1};
[Map2el,w{3}]=PCAHW3(XRe(:,ind),2);

figure();
plot(Map2el(1:178,2),Map2el(1:178,1),'*b');
hold();
plot(Map2el(179:end,2),Map2el(179:end,1),'or');
title('mRMR for 2 features then PCA');
mdl = fitcknn(Map2el,X(:,end),'NumNeighbors',5);
label=predict(mdl,Map2el);
disp(strcat('Error for mRMR-2:',num2str(abs(sum(label-X(:,65))))));


rec{2}=mrmr_mid_d(XRe,X(:,65),5),
ind=rec{2};
[Map5el,w{4}]=PCAHW3(XRe(:,ind),2);

figure();
plot(Map5el(1:178,2),Map5el(1:178,1),'*b');
hold();
plot(Map5el(179:end,2),Map5el(179:end,1),'or');
title('mRMR for 5 features then PCA');
mdl = fitcknn(Map5el,X(:,end),'NumNeighbors',5);
label=predict(mdl,Map5el);
disp(strcat('Error for mRMR-5:',num2str(abs(sum(label-X(:,65))))));

rec{3}=mrmr_mid_d(XRe,X(:,65),10),
ind=rec{3};
[Map5el,w{5}]=PCAHW3(XRe(:,ind),2);

figure();
plot(Map5el(1:178,2),Map5el(1:178,1),'*b');
hold();
plot(Map5el(179:end,2),Map5el(179:end,1),'or');
title('mRMR for 10 features then PCA');
mdl = fitcknn(Map5el,X(:,end),'NumNeighbors',5);
label=predict(mdl,Map5el);
disp(strcat('Error for mRMR-10:',num2str(abs(sum(label-X(:,65))))));


%%
%Question-3

%K-means clustering with last data obtained in Q2
[b,mean,error]=KmeansHW3(Map5el,2);
figure();
plot(Map5el(find(b(:,1)>0),2),Map5el(find(b(:,1)>0),1),'*b');
hold();
plot(Map5el(find(b(:,2)>0),2),Map5el(find(b(:,2)>0),1),'*r');
plot(mean(:,2),mean(:,1),'ok');
title('2-means Clustering');
legend('cluster-1','cluster-2','center-means');
disp(strcat('error for 2=',num2str(error)));

[b,mean,error]=KmeansHW3(Map5el,3);
figure();
plot(Map5el(find(b(:,1)>0),2),Map5el(find(b(:,1)>0),1),'*b');
hold();
plot(Map5el(find(b(:,2)>0),2),Map5el(find(b(:,2)>0),1),'*r');
plot(Map5el(find(b(:,3)>0),2),Map5el(find(b(:,3)>0),1),'*g');
plot(mean(:,2),mean(:,1),'ok');
title('3-means Clustering');
legend('cluster-1','cluster-2','cluster-3','center-means');
disp(strcat('error for 3=',num2str(error)));

[b,mean,error]=KmeansHW3(Map5el,4);
figure();
plot(Map5el(find(b(:,1)>0),2),Map5el(find(b(:,1)>0),1),'*b');
hold();
plot(Map5el(find(b(:,2)>0),2),Map5el(find(b(:,2)>0),1),'*r');
plot(Map5el(find(b(:,3)>0),2),Map5el(find(b(:,3)>0),1),'*g');
plot(Map5el(find(b(:,4)>0),2),Map5el(find(b(:,4)>0),1),'*c');
plot(mean(:,2),mean(:,1),'ok');
title('4-means Clustering');
legend('cluster-1','cluster-2','cluster-3','cluster-4','center-means');
disp(strcat('error for 4=',num2str(error)));

[mean,var]=EM(Map5el,2,100,[-0.01858 0.004171; -0.1686 0.1589]);
figure();
plot(Map5el(:,2),Map5el(:,1),'*c');
plot_gaussian_ellipsoid(fliplr(mean{1}.'),var{1},2);
meandummy=mean{1};
plot(meandummy(2),meandummy(1),'ob');
plot_gaussian_ellipsoid(fliplr(mean{2}.'),var{2},2);
meandummy=mean{2};
plot(meandummy(2),meandummy(1),'ob');
title('EM-2');
legend('data','Clusters');

[mean,var]=EM(Map5el,3,100,[0.1045 -0.083 -0.1686 ; 0.15 0.1589 -1.10]);
figure();
plot(Map5el(:,2),Map5el(:,1),'*c');
plot_gaussian_ellipsoid(fliplr(mean{1}.'),var{1},2);
plot_gaussian_ellipsoid(fliplr(mean{2}.'),var{2},2);
plot_gaussian_ellipsoid(fliplr(mean{3}.'),var{3},2);
meandummy=mean{1};
plot(meandummy(2),meandummy(1),'ob');
meandummy=mean{2};
plot(meandummy(2),meandummy(1),'ob');
meandummy=mean{3};
plot(meandummy(2),meandummy(1),'ob');
title('EM-3');
legend('data','Clusters');

[mean,var]=EM(Map5el,4,100,[0.1045 -0.083 -0.1686 2 ; 0.15 0.1589 -1.10 -1]);
figure();
plot(Map5el(:,2),Map5el(:,1),'*c');
plot_gaussian_ellipsoid(fliplr(mean{1}.'),var{1},2);
plot_gaussian_ellipsoid(fliplr(mean{2}.'),var{2},2);
plot_gaussian_ellipsoid(fliplr(mean{3}.'),var{3},2);
plot_gaussian_ellipsoid(fliplr(mean{4}.'),var{4},2);
meandummy=mean{1};
plot(meandummy(2),meandummy(1),'ob');
meandummy=mean{2};
plot(meandummy(2),meandummy(1),'ob');
meandummy=mean{3};
plot(meandummy(2),meandummy(1),'ob');
meandummy=mean{4};
plot(meandummy(2),meandummy(1),'ob');

title('EM-4');
legend('data','Clusters');


