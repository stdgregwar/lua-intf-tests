v = Foo()
range = 800
--first 
cstart = os.clock()
for i=1,range do
	v.val = i
	v:display()
end 
cstop = os.clock()



pstart = os.clock()
for i=1,range do
	v.val = i
	print(v.val)
end 
pstop = os.clock()

print("Display with cout took :".. (cstop-cstart))
print("Display with print took :".. (pstop-pstart))
