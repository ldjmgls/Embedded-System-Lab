import matplotlib.pyplot as plt
import numpy as np

Ts = 30;   # signal interval
end = 150; # signal end point
n = int(end/Ts)+1;

x = np.linspace(0, end, num=n) # signal vector

#TODO: revise this array to your results
y = np.array([0.000, 2.472, 12.199, 13.076, 13.235, 12.996]) # speed vector for counterclockwise
#y = np.array([0.000, 6.139, 7.335, 7.734, 7.973, 6.857]) # speed vector for clockwise
z = np.polyfit(x, y, 2) # Least squares polynomial fit, and return the coefficients.

goal = 8             # if we want to let the servo run at 7 cm/sec
                     # equation : z[0]*x^2 + z[1]*x + z[2] = goal
z[2] -= goal         # z[0]*x^2 + z[1]*x + z[2] - goal = 0

result = np.roots(z) # Return the roots of a polynomial with coefficients given

# output the correct one
if (0 <= result[0]) and (result[0] <= end):
    print(result[0])
else:
    print(result[1])