import re

file=open('test_nuisance.txt')
t=file.read()
z=t.split('\n')

name=[]
sf=[]

input_uncertainty = 0.2

for line in z:
    values=[]
    if line.find('SF') > 0: # the line contain information about SF
        polished_line=re.sub(' * |,|!','#',line)
        polished_list=polished_line.split('#')
        for i in polished_list: # in order are: background dx/sigma_in sigma_out/sigma_in ; signal dx/sigma_in sigma_out/sigma_in ; rho 
            try:
                l=eval(i)
                values.append(i)
#                print l
            except:
                if( i != '' ):
                    name.append(i)
                else:
                    continue
#                    print i + str(" is a string")
    if( len(values) > 0 ):
        sf.append(values)
    print values

print name
print sf


for i in range(0,len(name)):
    sf_i = 1+eval(sf[i][0])*input_uncertainty
    sf_e = eval(sf[i][1])*input_uncertainty
    print str(name[i]) + " associated with " + str(sf[i])
    print str(name[i]) + " associated with " + str(sf_i) + " pm " + str(sf_e) 
    
