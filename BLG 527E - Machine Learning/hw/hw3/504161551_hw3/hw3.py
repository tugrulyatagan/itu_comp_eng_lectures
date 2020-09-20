# BLG 527E Machine Learning HW3
# Author: Tugrul Yatagan 504161551

import sys
import time
import numpy
import pandas
from sklearn.neighbors import KNeighborsClassifier
from sklearn.discriminant_analysis import LinearDiscriminantAnalysis
from sklearn.neural_network import MLPClassifier
from sklearn.tree import DecisionTreeClassifier
from sklearn.metrics import accuracy_score
from sklearn.metrics import confusion_matrix
from sklearn.metrics import precision_score
from sklearn.model_selection import cross_val_score
from sklearn.model_selection import train_test_split


##################################
######## Read input files ########
##################################
if len(sys.argv) == 3:
    train_file_name = sys.argv[1]
    test_file_name = sys.argv[2]
else:
    train_file_name = 'optdigits.tra.txt'
    test_file_name = 'optdigits.tes.txt'

train_file = pandas.read_csv(train_file_name, header=None)
test_file = pandas.read_csv(test_file_name, header=None)

X_tra = numpy.array(train_file.ix[:, 0:63])
y_tra = numpy.array(train_file[64])

X_tes = numpy.array(test_file.ix[:, 0:63])
y_tes = numpy.array(test_file[64])


##################################
############## KNN ###############
##################################
def knn_find_optimum_k(X, y):
    # split into train and test with 90% - 10%
    X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.1)

    # instantiate learning model
    knn = KNeighborsClassifier()
    knn.fit(X_train, y_train)

    # create odd list of K for KNN optimization
    neighbors = range(1, 30, 2)  # 1, 3 ,5 ... ,29
    cv_scores = []

    # perform 10-fold cross validation
    for k in neighbors:
        knn = KNeighborsClassifier(n_neighbors=k)
        scores = cross_val_score(knn, X_train, y_train)
        cv_scores.append(scores.mean())

    optimum_k_neighbor = neighbors[cv_scores.index(max(cv_scores))]
    print "Optimum KNN k is %d with validation accuracy: %0.2f%%" % (optimum_k_neighbor, max(cv_scores) * 100)
    return optimum_k_neighbor

# knn get optimum k value
optimum_k = knn_find_optimum_k(X_tra, y_tra)

# knn measure training time on training data
knn_train_start = time.time()
knn = KNeighborsClassifier(n_neighbors=optimum_k)
knn.fit(X_tra, y_tra)
knn_train_pred = knn.predict(X_tra)
knn_train_end = time.time()

# knn measure test time on test data
knn_test_start = time.time()
knn_test_pred = knn.predict(X_tes)
knn_test_end = time.time()


##################################
############## LDA ###############
##################################
def lda_find_optimum_n(X, y):
    # split into train and test with 90% - 10%
    X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.1)

    # instantiate learning model
    lda = LinearDiscriminantAnalysis()
    lda = lda.fit(X_train, y_train)

    # create LDA number of components list for optimization
    component_numbers = range(2, 10)
    cv_scores = []

    # perform 10-fold cross validation
    for n in component_numbers:
        lda = LinearDiscriminantAnalysis(n_components=n)
        scores = cross_val_score(lda, X_train, y_train)
        cv_scores.append(scores.mean())

    optimum_n = component_numbers[cv_scores.index(max(cv_scores))]
    print "Optimum LDA component number is %d with validation accuracy: %0.2f%%" % (optimum_n, max(cv_scores) * 100)
    return optimum_n

# mlp get optimum layers
optimum_n = lda_find_optimum_n(X_tra, y_tra)

# lda measure training time on training data
lda_train_start = time.time()
lda = LinearDiscriminantAnalysis(n_components=optimum_n)
lda = lda.fit(X_tra, y_tra)
lda_train_pred = lda.predict(X_tra)
lda_train_end = time.time()

# lda measure test time on test data
lda_test_start = time.time()
lda_test_pred = lda.predict(X_tes)
lda_test_end = time.time()


##################################
############## MLP ###############
##################################
def mlp_find_optimum_layers(X, y):
    # split into train and test with 90% - 10%
    X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.1)

    # instantiate learning model
    mlp = MLPClassifier()
    mlp = mlp.fit(X_train, y_train)

    # create MLP layering candidate list for optimization
    layers = [(100,), (50,50), (33,33,33), (20,20,20,20,20)]
    cv_scores = []

    # perform 10-fold cross validation
    for l in layers:
        mlp = MLPClassifier(hidden_layer_sizes=l)
        scores = cross_val_score(mlp, X_train, y_train)
        cv_scores.append(scores.mean())

    optimum_layering = layers[cv_scores.index(max(cv_scores))]
    print "Optimum MLP layering is %s layer number is %d with validation accuracy: %0.2f%%" % (str(optimum_layering), len(optimum_layering), max(cv_scores) * 100)
    return optimum_layering

# mlp get optimum layers
optimum_layers = mlp_find_optimum_layers(X_tra, y_tra)

# mlp measure training time on training data
mlp_train_start = time.time()
mlp = MLPClassifier(hidden_layer_sizes=optimum_layers)
mlp = mlp.fit(X_tra, y_tra)
mlp_train_pred = mlp.predict(X_tra)
mlp_train_end = time.time()

# mlp measure test time on test data
mlp_test_start = time.time()
mlp_test_pred = mlp.predict(X_tes)
mlp_test_end = time.time()


##################################
######### Decision Tree ##########
##################################
def dtree_find_optimum_min_impurity(X, y):
    # split into train and test with 90% - 10%
    X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.1)

    # instantiate learning model
    dtree = DecisionTreeClassifier(criterion='entropy')
    dtree = dtree.fit(X_train, y_train)

    # create minimum impurity decrease candidate list for optimization
    min_impurity_list = [0, 0.1, 0.5, 1]
    cv_scores = []

    # perform 10-fold cross validation
    for i in min_impurity_list:
        dtree = DecisionTreeClassifier(criterion='entropy', min_impurity_decrease=i)
        scores = cross_val_score(dtree, X_train, y_train)
        cv_scores.append(scores.mean())

    optimum_min_impurity = min_impurity_list[cv_scores.index(max(cv_scores))]
    print "Optimum decision tree minimum impurity decrease is %0.2f with validation accuracy: %0.2f%%" % (optimum_min_impurity, max(cv_scores) * 100)
    return optimum_min_impurity

# decision tree get optimum min_impurity
optimum_min_impurity = dtree_find_optimum_min_impurity(X_tra, y_tra)

# decision tree measure training time on training data
dtree_train_start = time.time()
dtree = DecisionTreeClassifier(criterion='entropy', min_impurity_decrease=optimum_min_impurity)
dtree = dtree.fit(X_tra, y_tra)
dtree_train_pred = dtree.predict(X_tra)
dtree_train_end = time.time()

# decision tree measure test time on test data
dtree_test_start = time.time()
dtree_test_pred = dtree.predict(X_tes)
dtree_test_end = time.time()


##################################
############ Results #############
##################################
print '\n\n**** KNN ****'
print 'KNN Training accuracy: %0.2f' % (accuracy_score(y_tra, knn_train_pred) * 100)
print 'KNN Test accuracy: %0.2f' % (accuracy_score(y_tes, knn_test_pred) * 100)
print '\nKNN Training accuracy for each class:'
print [round(i,3) for i in precision_score(y_tra, knn_train_pred, average=None)]
print '\nKNN Test accuracy for each class:'
print [round(i,3) for i in precision_score(y_tes, knn_test_pred, average=None)]
print '\nKNN Training confusion matrix:'
print confusion_matrix(y_tra, knn_train_pred)
print '\nKNN Test confusion matrix:'
print confusion_matrix(y_tes, knn_test_pred)
print '\nKNN Training time: %f' % (knn_train_end - knn_train_start)
print 'KNN Test time: %f' % (knn_test_end - knn_test_start)

print '\n\n**** LDA ****'
print 'LDA Training accuracy: %0.2f' % (accuracy_score(y_tra, lda_train_pred) * 100)
print 'LDA Test accuracy: %0.2f' % (accuracy_score(y_tes, lda_test_pred) * 100)
print '\nLDA Training accuracy for each class:'
print [round(i,3) for i in precision_score(y_tra, lda_train_pred, average=None)]
print '\nLDA Test accuracy for each class:'
print [round(i,3) for i in precision_score(y_tes, lda_test_pred, average=None)]
print '\nLDA Training confusion matrix:'
print confusion_matrix(y_tra, lda_train_pred)
print '\nLDA Test confusion matrix:'
print confusion_matrix(y_tes, lda_test_pred)
print '\nLDA Training time: %f' % (lda_train_end - lda_train_start)
print 'LDA Test time: %f' % (lda_test_end - lda_test_start)

print '\n\n**** MLP ****'
print 'MLP Training accuracy: %0.2f' % (accuracy_score(y_tra, mlp_train_pred) * 100)
print 'MLP Test accuracy: %0.2f' % (accuracy_score(y_tes, mlp_test_pred) * 100)
print '\nMLP Training accuracy for each class:'
print [round(i,3) for i in precision_score(y_tra, mlp_train_pred, average=None)]
print '\nMLP Test accuracy for each class:'
print [round(i,3) for i in precision_score(y_tes, mlp_test_pred, average=None)]
print '\nMLP Training confusion matrix:'
print confusion_matrix(y_tra, mlp_train_pred)
print '\nMLP Test confusion matrix:'
print confusion_matrix(y_tes, mlp_test_pred)
print '\nMLP Training time: %f' % (mlp_train_end - mlp_train_start)
print 'MLP Test time: %f' % (mlp_test_end - mlp_test_start)

print '\n\n**** Decision Tree ****'
print 'Decision Tree Training accuracy: %0.2f' % (accuracy_score(y_tra, dtree_train_pred) * 100)
print 'Decision Tree Test accuracy: %0.2f' % (accuracy_score(y_tes, dtree_test_pred) * 100)
print '\nDecision Tree Training accuracy for each class:'
print [round(i,3) for i in precision_score(y_tra, dtree_train_pred, average=None)]
print '\nDecision Tree Test accuracy for each class:'
print [round(i,3) for i in precision_score(y_tes, dtree_test_pred, average=None)]
print '\nDecision Tree Training confusion matrix:'
print confusion_matrix(y_tra, dtree_train_pred)
print '\nDecision Tree Test confusion matrix:'
print confusion_matrix(y_tes, dtree_test_pred)
print '\nDecision Tree Training time: %f' % (dtree_train_end - dtree_train_start)
print 'Decision Tree Test time: %f' % (dtree_test_end - dtree_test_start)
