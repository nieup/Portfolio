## This Script creates the clean data set described in the Assignement 
## Please note that this code does NOT Merges the Inertial Signals 
## As refenced here : https://class.coursera.org/getdata-007/forum/thread?thread_id=49
## This seems a logical assumption we can not complete the asked steps (naming columns...)

## Features : 
features <- read.csv("features.txt", sep = " ", col.names = c("ref","feature"), 
                     header = FALSE)

Vect_features <- as.character(features$feature)

## Activity Labels : 
Labels_Ref <- read.csv("activity_labels.txt", header = FALSE, 
                       sep = " ", col.names = c("ref", "Label"))

Labels <- as.character(Labels_Ref$Label)


## Getting Test data : 
SubJ_Test <- read.table("test/subject_test.txt")
X_Test <- read.table("test/X_test.txt")
Y_Test <- read.table("test/y_test.txt")

## Cleaning the Test data
Clean_Test <- cbind(SubJ_Test, Y_Test, X_Test)
names(Clean_Test) <- c("Subject", "Label", Vect_features) ## Col Names 
Clean_Test$Label <- Labels[Clean_Test$Label] ## character Labels 


## Getting Train data : 
SubJ_Train <- read.table("train/subject_train.txt")
X_Train <- read.table("train/X_train.txt")
Y_Train <- read.table("train/y_train.txt")

## Cleaning the Train data
Clean_Train <- cbind(SubJ_Train, Y_Train, X_Train)
names(Clean_Train) <- c("Subject", "Label", Vect_features) ## Col Names 
Clean_Train$Label <- Labels[Clean_Train$Label] ## character Labels 

## Merging the entire data set 
Clean_Data <- rbind(Clean_Test, Clean_Train)

## Note : there will not be any diffrence anymore bettwen train and test data 

## Getting the columns containing "mean" as variable name : 
## Therefore including "meanFreq" measuements 
Index_Mean <- grep("mean", Vect_features )

## Getting the columns containing "std" as variable name :
Index_Std <- grep("std", Vect_features )

## Creating general Index : 
Index <- c(Index_Mean, Index_Std)
## Sorting Index (for fun)
Index <- sort(Index)

## Generating Selected features
Sel_features <- Vect_features[Index]

## We must keep the 2 first Columns, subject and Label for the tidy data : 
Index <- Index + 2 ## Moves everything to the right by 2 
Index <- c(1, 2, Index) ## Adds the 2 first columns 

## Generating "tidy_dataV1" version 1 : 
tidy_dataV1 <- Clean_Data[, Index]

## COMPUTING MEAN VALUES FOR Subject and Label Over feature 
## Creates Buffer matrix to store the reslut of mean calculation 
Matrix_tidy_Data <- matrix(nrow = 180, ncol = 81)

for (i in 1:30) { ## Select Subject : 
  Index_Subj <- (tidy_data$Subject == i)
  Buff_Data_Subj <- tidy_data[Index_Subj, ]
  for (j in 1:6){ ## Select Labels for Subject :
    Index_Label <- (Buff_Data_Subj$Label == Labels[j])
    Buff_Data_Subj_Label <- Buff_Data_Subj[Index_Label, ]
    ## Fill the 2 first columns of the matrix with subject id and Label id 
    Matrix_tidy_Data[i*6+j-6,1] <- i
    Matrix_tidy_Data[i*6+j-6,2] <- j
    for (k in 3:81){ ## mean over the column :
      Matrix_tidy_Data[i*6+j-6, k] <- mean(Buff_Data_Subj_Label[, k], na.rm = TRUE)
    }
  }  
}

## Generating final data set : 
tidy_Data <- data.frame(Matrix_tidy_Data)

## Cleanning final Data set : 
names(tidy_Data) <- c("Subject", "Label", Sel_features) ## Col names 
tidy_Data$Label <- Labels[tidy_Data$Label] ## character Labels 

## Saving data into txt file : 
write.table(tidy_Data, "tidy_Data.txt", row.name=FALSE)
