/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package blg546e.P;

import java.util.Objects;

/**
 *
 * @author ovatman
 */
public class Student {
    private String name;
    private long number;

    public Student(String name, long number) {
        this.name = name;
        this.number = number;
    }

    @Override
    public String toString() {
        return "Student{" + "name=" + name + ", number=" + number + "}\n";
    }

    @Override
    public int hashCode() {
        int hash = 7;
        hash = 53 * hash + (int) (this.number ^ (this.number >>> 32));
        return hash;
    }

    @Override
    public boolean equals(Object obj) {
        if (obj == null) {
            return false;
        }
        if (getClass() != obj.getClass()) {
            return false;
        }
        final Student other = (Student) obj;
        if (this.number != other.number) {
            return false;
        }
        return true;
    }



    
}
