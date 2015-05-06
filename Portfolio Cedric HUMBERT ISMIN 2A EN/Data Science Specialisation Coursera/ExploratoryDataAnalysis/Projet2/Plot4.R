## Plotting the evolution of the Emission of PM-25 in the USA through the years  
## 1999 and 2008 on Coal relateded Soureced We assume this corresponds to the 
## variable SCC = 10100101

## We assume we are in the correct directory 
## Importing data : (only what is necessary here, NEI) : 
NEI <- readRDS("summarySCC_PM25.rds")

## Generating Data : 
Index <- (NEI$SCC == 10100101)
Data <- NEI[Index, ]
Data_Sort <- c() ## initialise 
Data_Sort[1] <- sum(Data$Emission[which(Data$year == 1999)])
Data_Sort[2] <- sum(Data$Emission[which(Data$year == 2002)])
Data_Sort[3] <- sum(Data$Emission[which(Data$year == 2005)])
Data_Sort[4] <- sum(Data$Emission[which(Data$year == 2008)])

#Selecting Plotting device : 
png(file = "Plot 4.png")

#ploting : 
plot(Data_Sort, , type ="l", xaxt = "n",
     ylab ="Mass of Emissions (tons)", xlab="Year", 
     main = "Emissions of Coal related Souces (National)")
axis(1, at = 1:4, labels = c("1999","2002", "2005", "2008"))

#Turning Device off : 
dev.off()



