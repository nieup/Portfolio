## Plotting the evolution of the Total Emission of PM-25 on the city of Baltimore through the years  
## 1999 and 2008

## We assume we are in the correct directory 
## Importing data : (only what is necessary here, NEI) : 
NEI <- readRDS("summarySCC_PM25.rds")

# Generating Data : 
#Sum over the different sources of the total Emission in a Vector 
SumS[1] <- sum(NEI$Emission[which(NEI$year == 1999 & NEI$fips == 24510)])
SumS[2] <- sum(NEI$Emission[which(NEI$year == 2002 & NEI$fips == 24510)])
SumS[3] <- sum(NEI$Emission[which(NEI$year == 2005 & NEI$fips == 24510)])
SumS[4] <- sum(NEI$Emission[which(NEI$year == 2008 & NEI$fips == 24510)])

#Selecting Plotting device : 
png(file = "Plot 2.png")

#ploting : 
plot(SumS, ylab ="Total Emissions (tons)", xlab="Year", main = "Total Emission of PM-25 over Baltimore", type ="l", xaxt = "n")
axis(1, at = 1:4, labels = c("1999","2002", "2005", "2008"))

#Turning Device off : 
dev.off()