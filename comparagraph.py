import Image

f = Image.open('comparagraph.jpg')

# find file pixel size
x_max = f.size[0]
y_max = f.size[1]
i = 0
j = 0
count = 0

# load image
image = f.load()

# get pixels and write to csv file
f = open('comparagraph.csv', "w")

while i < x_max:
	while j < y_max:
		f.write(str(image[i,j][0])+",")
		# print image[i,j]
		j += 1
		count += 1
	i = i + 1
	j = 0 

f.close()

print count