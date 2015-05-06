## Plotting the evolution of the Total Emission of PM-25 through the years in the US 
## from 1999 through 2008

## We assume we are in the correct directory 
## Importing data : (only what is necessary here, NEI) : 
NEI <- readRDS("summarySCC_PM25.rds")

# Generating Data : 
#Sum over the different sources of the total Emission in a Vector 
SumS[1] <- sum(NEI$Emission[which(NEI$year == 1999)])
SumS[2] <- sum(NEI$Emission[which(NEI$year == 2002)])
SumS[3] <- sum(NEI$Emission[which(NEI$year == 2005)])
SumS[4] <- sum(NEI$Emission[which(NEI$year == 2008)])

#Selecting Plotting device : 
png(file = "Plot 1.png")

#ploting : 
plot(SumS, ylab ="Total Emissions (tons)", xlab="Year", main = "Total Emission of PM-25", type ="l", xaxt = "n")
axis(1, at = 1:4, labels = c("1999","2002", "2005", "2008"))

#Turning Device off : 
dev.off()