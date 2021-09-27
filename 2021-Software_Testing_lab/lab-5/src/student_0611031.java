import org.openqa.selenium.By;
import org.openqa.selenium.WebDriver;
import org.openqa.selenium.WebElement;
import org.openqa.selenium.WindowType;
import org.openqa.selenium.chrome.ChromeDriver;
import org.openqa.selenium.*;
import java.util.List;

public class student_0611031 {
    static public void main(String[] argv){
        System.setProperty("webdirver.chrome.driver","chromedriver.exe");
        WebDriver driver = new ChromeDriver();
        driver.get("https://www.nycu.edu.tw/");
        driver.manage().window().maximize();
        driver.findElement(By.linkText("消息")).click();
        driver.findElement(By.xpath("//*[@id=\"eael-advance-tabs-7dbbb0c\"]/div[2]/div[1]/ul")).findElement(By.tagName("li")).click();
        System.out.println(driver.findElement(By.tagName("h1")).getText());
        List<WebElement> context=driver.findElements(By.tagName("p"));
        for(int i=0;i<context.size();i++) {
            System.out.println(context.get(i).getText());
        }
//      part2
        driver.switchTo().newWindow(WindowType.TAB);
        driver.findElement(By.tagName("input")).sendKeys("0611031");
        driver.findElement(By.xpath("/html/body/div[1]/div[3]/form/div[1]/div[1]/div[3]/center")).findElement(By.tagName("input")).click();
        System.out.println(driver.findElement(By.xpath("//*[@id=\"rso\"]/div/div[2]/div/div/div[1]/a")).findElement(By.tagName("h3")).getText());
        driver.close();
    }
}