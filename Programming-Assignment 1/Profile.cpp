#include "Profile.h"

Profile::Profile(const std::string &email, const std::string &username, SubscriptionPlan plan) {
    this->email = email;
    this->username = username;
    this->plan = plan;
}

const std::string &Profile::getUsername() const {
    return this->username;
}

const std::string &Profile::getEmail() const {
    return this->email;
}

SubscriptionPlan Profile::getPlan() const {
    return this->plan;
}

LinkedList<Playlist> &Profile::getPlaylists() {
    return this->playlists;
}

LinkedList<Profile *> &Profile::getFollowings() {
    return this->following;
}

LinkedList<Profile *> &Profile::getFollowers() {
    return this->followers;
}

void Profile::setPlan(SubscriptionPlan plan) {
    this->plan = plan;
}

void Profile::followProfile(Profile *profile) {

    following.insertAtTheEnd(profile);
    (profile -> followers).insertAtTheEnd(this);
}

void Profile::unfollowProfile(Profile *profile) {

    following.removeNode(profile);
    (profile -> followers).removeNode(this);
}

void Profile::createPlaylist(const std::string &playlistName) {

    Playlist newplaylist(playlistName);
    playlists.insertAtTheEnd(newplaylist);
}

void Profile::deletePlaylist(int playlistId) {

    
    Node<Playlist> *tmp_head = playlists.getFirstNode();
    	
	while ((tmp_head -> data).getPlaylistId() != playlistId) tmp_head = tmp_head -> next;
    
    playlists.removeNode(tmp_head);
}

void Profile::addSongToPlaylist(Song *song, int playlistId) {

    Playlist *ply = getPlaylist(playlistId);
    (*ply).addSong(song);
}

void Profile::deleteSongFromPlaylist(Song *song, int playlistId) {

    Playlist *ply = getPlaylist(playlistId);
    (*ply).dropSong(song);
}

Playlist *Profile::getPlaylist(int playlistId) {

    
    Node<Playlist> *tmp_head = playlists.getFirstNode();
    
    while ((tmp_head -> data).getPlaylistId() != playlistId) tmp_head = tmp_head -> next;
    
    return &(tmp_head -> data);
}

LinkedList<Playlist *> Profile::getSharedPlaylists() {

    Node<Profile *> *following_head = following.getFirstNode();
    LinkedList<Playlist *> result;
    Node<Playlist> *playlist_head;
    
    int i = 0, j;
    	
    while (i < following.getSize()){
    		
		playlist_head = ((*(following_head -> data)).getPlaylists()).getFirstNode();
		j = 0;
		
		while (j < ((*(following_head -> data)).getPlaylists()).getSize()){
			
			if ((playlist_head -> data).isShared()){
				result.insertAtTheEnd(&(playlist_head -> data));
			}
			
			playlist_head = playlist_head -> next;
			j++;
		}
		following_head = following_head -> next;
		i++;		
	}
	
	return result;
}

void Profile::shufflePlaylist(int playlistId, int seed) {

    Playlist *ply = getPlaylist(playlistId);
    (*ply).shuffle(seed);
}

void Profile::sharePlaylist(int playlistId) {

    Playlist *ply = getPlaylist(playlistId);
    (*ply).setShared(true);
}

void Profile::unsharePlaylist(int playlistId) {

    Playlist *ply = getPlaylist(playlistId);
    (*ply).setShared(false);
}

bool Profile::operator==(const Profile &rhs) const {
    return this->email == rhs.email && this->username == rhs.username && this->plan == rhs.plan;
}

bool Profile::operator!=(const Profile &rhs) const {
    return !(rhs == *this);
}

std::ostream &operator<<(std::ostream &os, const Profile &profile) {
    os << "email: " << profile.email << " |";
    os << " username: " << profile.username << " |";
    if (profile.plan == free_of_charge) {
        os << " plan: " << "free_of_charge" << " |";
    } else if (profile.plan == premium) {
        os << " plan: " << "premium" << " |";
    } else {
        os << " plan: " << "undefined" << " |";
    }

    os << " playlists: [";
    Node<Playlist> *firstPlaylistNode = profile.playlists.getFirstNode();
    Node<Playlist> *playlistNode = firstPlaylistNode;
    if (playlistNode) {
        do {
            os << playlistNode->data;
            if (playlistNode->next != firstPlaylistNode) os << ", ";
            playlistNode = playlistNode->next;
        } while (playlistNode != firstPlaylistNode);
    }
    os << "] |";
    os << " following: [";
    Node<Profile *> *firstProfileNode = profile.following.getFirstNode();
    Node<Profile *> *profileNode = firstProfileNode;
    if (profileNode) {
        do {
            os << profileNode->data->getEmail();
            if (profileNode->next != firstProfileNode) os << ", ";
            profileNode = profileNode->next;
        } while (profileNode != firstProfileNode);
    }
    os << "] |";
    os << " followers: [";
    firstProfileNode = profile.followers.getFirstNode();
    profileNode = firstProfileNode;
    if (profileNode) {
        do {
            os << profileNode->data->getEmail();
            if (profileNode->next != firstProfileNode) os << ", ";
            profileNode = profileNode->next;
        } while (profileNode != firstProfileNode);
    }
    os << "]";

    return os;
}
