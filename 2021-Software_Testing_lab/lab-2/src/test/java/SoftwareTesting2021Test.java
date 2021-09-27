import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.extension.ExtendWith;
import org.mockito.Mock;
import org.mockito.Spy;
import org.mockito.junit.jupiter.MockitoExtension;

import java.util.ArrayList;

import static org.junit.jupiter.api.Assertions.*;
import static org.mockito.Mockito.*;

@ExtendWith(MockitoExtension.class)

class SoftwareTesting2021Test {
        SoftwareTesting2021 softwareTesting2021=new SoftwareTesting2021();
        @Mock
        Date date;
        @Spy
        Hospital hospital;

        @Test
        void test_a() throws InterruptedException {
            Student student_a=new Student();
            when(date.getWeekday()).thenReturn(4);
            softwareTesting2021.date=date;
            softwareTesting2021.setHospital(hospital);
            softwareTesting2021.enterClass(student_a);
            assertEquals(softwareTesting2021.enterClass(student_a),"No class today");
            verify(softwareTesting2021.hospital,never()).treatment(student_a);
        }
        @Test
        void test_b() throws InterruptedException {
            Student student_b=new Student();
            when(date.getWeekday()).thenReturn(5);
            doNothing().when(hospital).isolation(student_b);
            softwareTesting2021.date=date;
            softwareTesting2021.setHospital(hospital);
            assertEquals(softwareTesting2021.enterClass((student_b)),"After a long time treatment. The student can get out! ^__^");
            verify(softwareTesting2021.hospital).treatment(student_b);
        }
        @Test
        void test_c() throws InterruptedException {
            ArrayList<String> student_list=new ArrayList();
            student_list.add("0611031");
            student_list.add("0611103");
            student_list.add("0856017");
            for(String student_id : student_list){
                Student student_group=new Student(student_id,38);
                doNothing().when(hospital).isolation(student_group);
                hospital.treatment(student_group);
                verify(hospital).treatment(student_group);

            }
            assertEquals(student_list,hospital.getLog());
        }
        @Test
        void test_d() throws InterruptedException {
            SoftwareTesting2021 mocksoftwareTesting2021=mock(SoftwareTesting2021.class);
            when(mocksoftwareTesting2021.getScore("11")).thenReturn(100);
            assertEquals(100,mocksoftwareTesting2021.getScore("11"));
        }

        public class Fakepaypal implements paypalService{
            public String doDonate(){
                return "successed";
            }
        }

        @Test
        void test_e() throws InterruptedException {
            Fakepaypal fakepaypal=new Fakepaypal();
            assertEquals("Thank you",softwareTesting2021.donate(fakepaypal));
        }
}
