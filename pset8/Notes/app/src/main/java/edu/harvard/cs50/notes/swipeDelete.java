package edu.harvard.cs50.notes;

import androidx.recyclerview.widget.ItemTouchHelper;
import androidx.recyclerview.widget.RecyclerView;

public class swipeDelete extends ItemTouchHelper.SimpleCallback {
    private NotesAdapter swipeAdapter;
    public swipeDelete(NotesAdapter calledAdapter) {
        super(0, ItemTouchHelper.LEFT | ItemTouchHelper.RIGHT);
        swipeAdapter = calledAdapter;
    }

    @Override
    public void onSwiped(RecyclerView.ViewHolder viewHolder, int direction) {
        int position = viewHolder.getAdapterPosition();
        swipeAdapter.deleteItem(position);
    }

    @Override
    public boolean onMove(RecyclerView recyclerView, RecyclerView.ViewHolder a, RecyclerView.ViewHolder b) {
        return false;
    }
}
