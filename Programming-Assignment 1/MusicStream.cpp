#include "MusicStream.h"

#include <iostream>

void MusicStream::addProfile(const std::string &email, const std::string &username, SubscriptionPlan plan) {

    Profile newprofile(email, username, plan);
    profiles.insertAtTheEnd(newprofile);
}

void MusicStream::deleteProfile(const std::string &email) {

    Node<Profile> *profiles_head = profiles.getFirstNode();
    LinkedList<Profile *> following_list, followers_list;
    Node<Profile *> *followings_head, *followers_head;
	int following_size, followers_size, i = 0, j = 0;
    
    LinkedList<Playlist> playlist_list;
    
    while ((profiles_head -> data).getEmail() != email) profiles_head = profiles_head -> next;
    
    following_list = (profiles_head -> data).getFollowings();
    followers_list = (profiles_head -> data).getFollowers();
    playlist_list = (profiles_head -> data).getPlaylists();
    
	following_size = following_list.getSize();
    followers_size = followers_list.getSize();
    
    followings_head = following_list.getFirstNode();
    followers_head = followers_list.getFirstNode();
    
    playlist_list.removeAllNodes();
	
	while (i < followers_size){
    	(*(followers_head -> data)).unfollowProfile(&(profiles_head -> data));
    	followers_head = followers_head -> next;
    	i++;
	}
	
	while (j < following_size){
		(profiles_head -> data).unfollowProfile(followings_head -> data);
		followings_head = followings_head -> next;
		j++;
	}
	
	profiles.removeNode(profiles_head);
}

void MusicStream::addArtist(const std::string &artistName) {

    Artist newartist(artistName);
    artists.insertAtTheEnd(newartist);
}

void MusicStream::addAlbum(const std::string &albumName, int artistId) {

    Album newalbum(albumName);
    Node<Album> *newalbumptr;
    Node<Artist> *tmp_head = artists.getFirstNode();
       	
	albums.insertAtTheEnd(newalbum);
	newalbumptr = albums.getLastNode();
    
    while ((tmp_head -> data).getArtistId() != artistId) tmp_head = tmp_head -> next;
	
	(tmp_head -> data).addAlbum(&(newalbumptr -> data));
}

void MusicStream::addSong(const std::string &songName, int songDuration, int albumId) {

    Song newsong(songName, songDuration);
    Node<Song> *newsongptr;
	Node<Album> *tmp_head = albums.getFirstNode();
	
	songs.insertAtTheEnd(newsong);
	newsongptr = songs.getLastNode();
    
    while ((tmp_head -> data).getAlbumId() != albumId) tmp_head = tmp_head -> next;
    
    (tmp_head -> data).addSong(&(newsongptr -> data));
}

void MusicStream::followProfile(const std::string &email1, const std::string &email2) {

    int usr1_found = 0, usr2_found = 0;
    Node<Profile> *profiles_head = profiles.getFirstNode(), *usr1ptr, *usr2ptr;
    
    while (!(usr1_found && usr2_found)){
    	if  ((profiles_head -> data).getEmail() == email1){
    		
    		usr1_found = 1;
    		usr1ptr = profiles_head;
		}
    	
		else if ((profiles_head -> data).getEmail() == email2){
			
			usr2_found = 1;
			usr2ptr = profiles_head;
		}
    	
    	profiles_head = profiles_head -> next;
	}
	
	(usr1ptr -> data).followProfile(&(usr2ptr -> data));
}

void MusicStream::unfollowProfile(const std::string &email1, const std::string &email2) {

    int usr1_found = 0, usr2_found = 0;
    Node<Profile> *profiles_head = profiles.getFirstNode(), *usr1ptr, *usr2ptr;
    
     while (!(usr1_found && usr2_found)){
    	if  ((profiles_head -> data).getEmail() == email1){
    		
    		usr1_found = 1;
    		usr1ptr = profiles_head;
		}
    	
		else if ((profiles_head -> data).getEmail() == email2){
			
			usr2_found = 1;
			usr2ptr = profiles_head;
		}
    	
    	profiles_head = profiles_head -> next;
	}
	
	(usr1ptr -> data).unfollowProfile(&(usr2ptr -> data));
}

void MusicStream::createPlaylist(const std::string &email, const std::string &playlistName) {

    Node<Profile> *profiles_head = profiles.getFirstNode();
    
    while ((profiles_head -> data).getEmail() != email) profiles_head = profiles_head -> next;
    
    (profiles_head -> data).createPlaylist(playlistName);
}

void MusicStream::deletePlaylist(const std::string &email, int playlistId) {

    Node<Profile> *profiles_head = profiles.getFirstNode();
    
    while ((profiles_head -> data).getEmail() != email) profiles_head = profiles_head -> next;
    
    (profiles_head -> data).deletePlaylist(playlistId);
}

void MusicStream::addSongToPlaylist(const std::string &email, int songId, int playlistId) {

    Node<Profile> *profiles_head = profiles.getFirstNode();
    Node<Song> *songs_head = songs.getFirstNode();
    
    while ((profiles_head -> data).getEmail() != email) profiles_head = profiles_head -> next;
    while ((songs_head -> data).getSongId() != songId) songs_head = songs_head -> next;
    
    (profiles_head -> data).addSongToPlaylist(&(songs_head -> data), playlistId);
    
}

void MusicStream::deleteSongFromPlaylist(const std::string &email, int songId, int playlistId) {

    Node<Profile> *profiles_head = profiles.getFirstNode();
    Node<Song> *songs_head = songs.getFirstNode();
    
    while ((profiles_head -> data).getEmail() != email) profiles_head = profiles_head -> next;
    while ((songs_head -> data).getSongId() != songId) songs_head = songs_head -> next;
    
    (profiles_head -> data).deleteSongFromPlaylist(&(songs_head -> data), playlistId);
}

LinkedList<Song *> MusicStream::playPlaylist(const std::string &email, Playlist *playlist) {

    Node<Profile> *profiles_head = profiles.getFirstNode();
    LinkedList<Song *> result = (*playlist).getSongs();
    
    while ((profiles_head -> data).getEmail() != email) profiles_head = profiles_head -> next;
    
    if ((profiles_head -> data).getPlan() == premium) return result;
    
    else if ((profiles_head -> data).getPlan() == free_of_charge){
		
		result.insertAsEveryKthNode(&(Song::ADVERTISEMENT_SONG), 2);
		
		return result;
	}
}

Playlist *MusicStream::getPlaylist(const std::string &email, int playlistId) {

    Node<Profile> *profiles_head = profiles.getFirstNode();
    
    while ((profiles_head -> data).getEmail() != email) profiles_head = profiles_head -> next;
    
    return (profiles_head -> data).getPlaylist(playlistId);
}

LinkedList<Playlist *> MusicStream::getSharedPlaylists(const std::string &email) {

    Node<Profile> *profiles_head = profiles.getFirstNode();
    
    while ((profiles_head -> data).getEmail() != email) profiles_head = profiles_head -> next;
    
    return (profiles_head -> data).getSharedPlaylists();
}

void MusicStream::shufflePlaylist(const std::string &email, int playlistId, int seed) {

    Node<Profile> *profiles_head = profiles.getFirstNode();
    
    while ((profiles_head -> data).getEmail() != email) profiles_head = profiles_head -> next;
    
    (*((profiles_head -> data).getPlaylist(playlistId))).shuffle(seed);
}

void MusicStream::sharePlaylist(const std::string &email, int playlistId) {

    Node<Profile> *profiles_head = profiles.getFirstNode();
    
    while ((profiles_head -> data).getEmail() != email) profiles_head = profiles_head -> next;
    
    (profiles_head -> data).sharePlaylist(playlistId);
}

void MusicStream::unsharePlaylist(const std::string &email, int playlistId) {

    Node<Profile> *profiles_head = profiles.getFirstNode();
    
    while ((profiles_head -> data).getEmail() != email) profiles_head = profiles_head -> next;
    
    (profiles_head -> data).unsharePlaylist(playlistId);
}

void MusicStream::subscribePremium(const std::string &email) {

    Node<Profile> *profiles_head = profiles.getFirstNode();
    
    while ((profiles_head -> data).getEmail() != email) profiles_head = profiles_head -> next;
    
    (profiles_head -> data).setPlan(premium);
}

void MusicStream::unsubscribePremium(const std::string &email) {

    Node<Profile> *profiles_head = profiles.getFirstNode();
    
    while ((profiles_head -> data).getEmail() != email) profiles_head = profiles_head -> next;
    
    (profiles_head -> data).setPlan(free_of_charge);
}

void MusicStream::print() const {
    std::cout << "# Printing the music stream ..." << std::endl;

    std::cout << "# Number of profiles is " << profiles.getSize() << ":" << std::endl;
    profiles.print();

    std::cout << "# Number of artists is " << artists.getSize() << ":" << std::endl;
    artists.print();

    std::cout << "# Number of albums is " << albums.getSize() << ":" << std::endl;
    albums.print();

    std::cout << "# Number of songs is " << songs.getSize() << ":" << std::endl;
    songs.print();

    std::cout << "# Printing is done." << std::endl;
}
