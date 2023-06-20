import java.util.ArrayList;
import java.util.List;

interface Content {

    String notificationMessage();

}

class NotificationService {
    private final List<User> subscribers;

    NotificationService() {
        this.subscribers = new ArrayList<User>();
    }

    public void subscribe(User user) {
        subscribers.add(user);
    }

    public void unsubscribe(User user) {
        subscribers.remove(user);
    }

    public void notifysubscribers(String message) {
        subscribers.forEach(subscriber -> subscriber.notify(message));
    }
}

class Channel {

    private String channelName;
    private final NotificationService notificationService;


    Channel(String channelName) {
        this.notificationService = new NotificationService();
        this.channelName = channelName;
    }

    public void publish(Content newContent) {
        String message = ": Channel " +  channelName + newContent.notificationMessage();
        notificationService.notifysubscribers(message);
    }

    public void subscribe(User newSubscriber) {
        notificationService.subscribe(newSubscriber);
    }

    public void unsubscribe(User unSubscriber) {
        notificationService.unsubscribe(unSubscriber);
    }
}

class User {
    private String name;
    public void notify(String message) {
        System.out.println(name + message);
    }

    public User(String name) {
        this.name = name;
    }
}


class Video implements Content {
    String name;
    public String notificationMessage() {
        return " published new Video: " + name;
    }

    public Video(String name) {
        this.name = name;
    }
}

class Shorts implements Content {
    String name;
    @Override
    public String notificationMessage() {
        return " published new Shorts: " + name;
    }

    public Shorts(String name) {
        this.name = name;
    }

}


class LiveStream implements Content {
    String name;
    @Override
    public String notificationMessage() {
        return " is going live: " + name;
    }

    public LiveStream(String name) {
        this.name = name;
    }
}


public class Main {
    public static void main(String[] args) {

        User user1 = new User("Alice");
        User user2 = new User("Bob");

        Channel channel1 = new Channel("Discovery");
        Channel channel2 = new Channel("Pewdiepie");
        Channel channel3 = new Channel("Innopolis");


        channel1.subscribe(user1);
        channel2.subscribe(user2);
        channel3.subscribe(user1);
        channel3.subscribe(user2);


        channel1.publish(new Video("Animals in Australia"));
        channel2.publish(new Shorts("Minecraft"));
        channel3.publish(new LiveStream("Report from rainforest"));

        channel3.unsubscribe(user1);

        channel1.publish(new Video("Scuba diving in Great Barrier Reef"));
        channel2.publish(new Shorts("Fortnite montage"));
        channel3.publish(new LiveStream("Jungle survival tips"));

    }
}