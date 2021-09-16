%This class is used for MATLAB based code for calculating Polar values

classdef Polar
    properties
        magnitude 
        theta 
    end
    methods
        function obj = Polar(z)
            x = real(z);
            y = imag(z);
            obj.magnitude = sqrt(x^2+y^2);
            obj.theta = atan2d(y,x);
        end
        function x = Re(obj)
            x = obj.magnitude*cosd(obj.theta);
        end
        function y = Im(obj)
            y = obj.magnitude*sind(obj.theta);
        end
        function add = plus(obj1, obj2)
            x = Re(obj1) + Re(obj2);
            y = Im(obj1) + Im(obj2);
            add = Polar(0);
            add.magnitude = sqrt(x^2+y^2);
            add.theta = atan2d(y,x);
        end
        function subtract = minus(obj1, obj2)
            x = Re(obj1) - Re(obj2);
            y = Im(obj1) - Im(obj2);
            subtract = Polar(0);
            subtract.magnitude = sqrt(x^2+y^2);
            subtract.theta = atan2d(y,x);
        end
        function division = mrdivide(obj1, obj2)
            division = Polar(0);
            division.magnitude = obj1.magnitude/obj2.magnitude;
            angle = obj1.theta - obj2.theta;
            
            if angle > 180
                angle = angle - 360;
            end
            if angle < -180
                angle = angle + 360;
            end
            
            division.theta = angle;
        end
        function product = mtimes(obj1, obj2)
            product = Polar(0);
            product.magnitude = obj1.magnitude*obj2.magnitude;
            angle = obj1.theta + obj2.theta;
            
            if angle > 180
                angle = angle - 360;
            end
            if angle < -180
                angle = angle + 360;
            end
            
            product.theta = angle;
            
        end
        function rectangular = cr(obj1)
            rectangular(1) = Re(obj1);
            rectangular(2) = Im(obj1);
        end
        function y = pr(obj1, obj2)
            z_1 = complex(Re(obj1), Im(obj1));
            z_2 = complex(Re(obj2), Im(obj2));
            y = Polar((z_1*z_2)/(z_1 + z_2));
        end
    end
end
