from collections import Counter
import string
'''
http://osandamalith.wordpress.com
This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. 
'''

cipher = "F96DE8C227A259C87EE1DA2AED57C93FE5DA36ED4EC87EF2C63AAE5B9A7EFFD673BE4ACF7BE8923CAB1ECE7AF2DA3DA44FCF7AE29235A24C963FF0DF3CA3599A70E5DA36BF1ECE77F8DC34BE129A6CF4D126BF5B9A7CFEDF3EB850D37CF0C63AA2509A76FF9227A55B9A6FE3D720A850D97AB1DD35ED5FCE6BF0D138A84CC931B1F121B44ECE70F6C032BD56C33FF9D320ED5CDF7AFF9226BE5BDE3FF7DD21ED56CF71F5C036A94D963FF8D473A351CE3FE5DA3CB84DDB71F5C17FED51DC3FE8D732BF4D963FF3C727ED4AC87EF5DB27A451D47EFD9230BF47CA6BFEC12ABE4ADF72E29224A84CDF3FF5D720A459D47AF59232A35A9A7AE7D33FB85FCE7AF5923AA31EDB3FF7D33ABF52C33FF0D673A551D93FFCD33DA35BC831B1F43CBF1EDF67F0DF23A15B963FE5DA36ED68D378F4DC36BF5B9A7AFFD121B44ECE76FEDC73BE5DD27AFCD773BA5FC93FE5DA3CB859D26BB1C63CED5CDF3FE2D730B84CDF3FF7DD21ED5ADF7CF0D636BE1EDB79E5D721ED57CE3FE6D320ED57D469F4DC27A85A963FF3C727ED49DF3FFFDD24ED55D470E69E73AC50DE3FE5DA3ABE1EDF67F4C030A44DDF3FF5D73EA250C96BE3D327A84D963FE5DA32B91ED36BB1D132A31ED87AB1D021A255DF71B1C436BF479A7AF0C13AA14794"

ENGLISH_FREQ = {'A':0.08167, 'B':0.01492, 'C':0.02782, 'D':0.04253, 'E':0.12702,
                'F':0.02228, 'G':0.02015, 'H':0.06094, 'I':0.06966, 'J':0.00153,
                'K':0.00772, 'L':0.04025, 'M':0.02406, 'N':0.06749, 'O':0.07507,
                'P':0.01929, 'Q':0.00095, 'R':0.05987, 'S':0.06327, 'T':0.09056,
                'U':0.02758, 'V':0.00978, 'W':0.02360, 'X':0.00150, 'Y':0.01974,
                'Z':0.00074}

number = range(48,58)
upper_case = string.ascii_uppercase
lower_case = string.ascii_lowercase
lst_cipher = [cipher[i:i+2] for i in range(0,len(cipher),2)]
key_length=7

def hexxor(a, b):
    return "".join(["%x" % (int(x, 16) ^ int(y, 16)) for (x, y) in zip(a, b)])

# break cipher into shift into each block of key length
def shift_chunk():
    shift=[]
    for i in range(key_length):
        shift.append(lst_cipher[i::key_length])
    return shift

shift = shift_chunk()

# calculate frequency of each hex character in cipher
def letter_count(message):
    mes_lst = [message[i:i+2] for i in range(0,len(message),2)]
    return dict((k, v) for k,v in Counter(mes_lst).most_common())

# calculate frequency of each letter in any message
def letter_count_2(message):
    return dict((k, v) for k,v in Counter(message).most_common())

# calculate index of coincidence of cipher
# as result, we achieve max IC and assume key length is corresponding
def calculateIC(message):
        cipher = message
        dict_IC = {}
        for key in range(1,14):
            average_IC = 0
            for i in range(key):
                t_cipher = ''.join([cipher[i:i+2] for i in range(0,len(message),2*key)])
                num_letter = letter_count(t_cipher)
                IC = 0
                fixed = len(t_cipher)/2*(len(t_cipher)/2-1)
                for i in num_letter:
                    f = num_letter[i]*(num_letter[i]-1)
                    if fixed == 0:
                        IC+=0
                    else:
                        IC += float(f)/fixed
                average_IC += IC
            dict_IC[key] = average_IC/(key)
        return dict_IC

# calculate all of candidate byte that XOR with each shift we get result that
# in range (32,126) and not a number
def guess_byte(n):
    right_guess=[]
    for i in range(255):
        hex_i = '{:02X}'.format(i)
        k=0
        for j in shift[n]:
            c = int(hexxor(hex_i,j),16)
            if c<32 or c>126 or c in number:
                break
            k+=1
        if k==len(shift[n]):
            right_guess.append(hex_i)
    return right_guess

# calculate chi square of message
def chi_square(mess):
    t_mess=""
    for i in mess:
        if i in lower_case or i in upper_case:
            t_mess+=i
    chi = 0
    t_mess = t_mess.upper()
    dic_mess =  letter_count_2(t_mess)
    for i in upper_case:
        b = ENGLISH_FREQ[i]*len(t_mess)
        if i in dic_mess:
            a = (dic_mess[i] - b)**2
            chi += a/b
        else:
            chi+=b
    return chi

# calculate all ci square of all messages those are correspond with guess byte
# obtain the min chi
def chiCal(index):
    guess_list = guess_byte(index)
    chi = {}
    for i in guess_list:
        guess_mess=[]
        for j in shift[index]:
            guess_mess.append(hexxor(i,j).decode('hex'))
        chi[i] = chi_square(''.join(guess_mess))
    min_chi = min(chi, key=chi.get)
    return min_chi


# calculate key
key=""
for i in range(key_length):
    key+= chiCal(i)

# calculate plaintext
plaintext=""
for i in range(0,len(cipher),key_length*2):
    plaintext+=hexxor(cipher[i:i+key_length*2],key).decode('hex')

print 'Key: \n' + ', '.join(['0x' + key[i:i+2] for i in range(0, len(key), 2)])
print 'Text: \n' + plaintext
