


length = 1
n_separators = 11
width = 1



start_pos = -length/2
end_pos = length

for i in range(n_separators):
	print(n_separators, start_pos + (length * (i+1)/(n_separators+1)), 1/(n_separators + 1))
