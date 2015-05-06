## Plotting the evolution of the Emission of PM-25 by type on the city of Baltimore through the 
## years 1999 and 2008 using ggplo2

## We assume we are in the correct directory 

## library : 
library(ggplot2)

## Importing data : (only what is necessary here, NEI) : 
NEI <- readRDS("summarySCC_PM25.rds")

## Extract data corresponding to Baltimore fips = 24510 
Index <- (NEI$fips == 24510)
Data <- NEI[Index,]

#Selecting Plotting device : 
png(file = "Plot 3.png")

#ploting : 
qplot(year, Emissions, data = Data, facets = ~type, 
      xlab = "Year", ylab = "Emission de PM-25 (tons)", 
      main = "Evolution of Sources of Pollution through time",  
      geom = c("point", "smooth"), method = "glm", 
      size = I(2), color = type, na.rm = TRUE, ylim = c(0, 5))

## Please note that the scale does not permit to see the entire data 
## I tried a logarithmic scale for the Emissions but the Smoothing produced errors
## Note that the majority of the data is here it can be proved using box_plots  
## However displayng them on the same graph was not possible 

#Turning Device off : 
dev.off()








