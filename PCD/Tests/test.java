class ThreadDemo extends Thread
{
    public static void main (String[] args) {
        ThreadDemo t = new ThreadDemo();
        t.start();
        System.out.println("one. ");

        ThreadDemo p = new ThreadDemo();
        p.start();
        System.out.println("two. ");
    }

    public void run () {
        System.out.println("Thread ");
    }
}